#include <cstdlib>
#include "Citizen.h"
#include "../Bank/BankRule.h"
#include "../Work/WorkRule.h"
#include "../Home/HomeRule.h"
#include "../Food/FoodRule.hpp"
#include "../Store/StoreRule.h" 
#include "../Plot/PlotSystem.h"
#include "../School/SchoolRule.h" 
#include "../Hospital/HospitalRule.h" 
#include "../Hospital/HospitalSystem.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/PathFinder/PathFinder.hpp"
#include "../../Helpers/HelperFunctions.h"
#include "../../Helpers/Government.h"
#include "../../Helpers/Constants.h"
#include "CitizenSystem.h"


Citizen::Citizen(Plot* plot) : target(nullptr), currentPlot(plot), currentRoad(nullptr), activeRule(nullptr), money(1000), tempTarget(plot->Coords()), coords(plot->Coords()), doubleSpeedTime(0),
                               waitTime(0.f), forceWait(0.f), inPlot(false), pathFindFailed(false), dead(false)
{
    age = RandomInt(7, 13) * 3;
	gender = static_cast<Gender>(RandomInt(0, 2));
    
    moveSpeed = 1.5f + static_cast<float>(RandomInt(-30, 30)) / 100;
    
    shape = sf::CircleShape(5);
    shape.setFillColor(BLUE);
    plot->Enter(this);
    GenRules();
}

Citizen::Citizen(Plot* plot, Citizen* parent1, Citizen* parent2) : Citizen(plot)
{
    age = 0;
    money = 0;
	Relationship char1, char2;
	parent1->GetGender() == MALE ? (char1 = FATHER, char2 = MOTHER) : (char1 = MOTHER, char2 = FATHER);
	SetRelationships(char1, parent1);
	SetRelationships(char2, parent2);
    plot->Enter(this);
	parent1->descendants.InsertLast(this);
	parent2->descendants.InsertLast(this);
}

Citizen::~Citizen()
{
	const auto myBankRule = dynamic_cast<BankRule*>(FindRule(BANK));
    
    Government::AddTax(float(myBankRule->GetSavings()) / 3);
    
    const auto relation = gender == MALE ? FATHER : MOTHER;
    // TODO : money goes to children?
	for (auto child : descendants)
	{
		child->SetRelationships(relation, nullptr);
		auto childBankRule = dynamic_cast<BankRule*>(child->FindRule(BANK));
		childBankRule->SaveMoney(float(myBankRule->GetSavings()) / descendants.Count() / 2);
	}
    
	auto fatherPtr = GetFamilyMember(FATHER);
	auto motherPtr = GetFamilyMember(MOTHER);
	auto spousePtr = GetFamilyMember(SPOUSE);
	auto homeRulePtr = dynamic_cast<HomeRule*>(FindRule(HOME));
	if (fatherPtr != nullptr)
	{
		fatherPtr->descendants.Remove(this);
	}
	if (motherPtr != nullptr)
	{
		motherPtr->descendants.Remove(this);
	}
	if (spousePtr != nullptr)
	{
		spousePtr->SetRelationships(SPOUSE, nullptr);
	}
	if (homeRulePtr != nullptr)
	{
		homeRulePtr->Unregister();
	}
    
    if (currentPlot != nullptr)
    {
        currentPlot->Leave(this);
    }
    if (currentRoad != nullptr)    
    {
        currentRoad->Leave();
    }
    rules.Dispose();
}

/**
 * \brief Increases (decrease if negative) the amount of money of the citizen
 * \param m Amount of money to increase by (give negative to reduce)
 * \return Returns true if transaction is doable (money is more than paid)
 */
bool Citizen::IncreaseMoney(const int m)
{
    if (money + m < 0)
    {
        return false;
    }
    money += m;
    return true;
}

/**
 * \brief Sets the citizen to target a plot
 * \param t Pointer to target plot      
 */
void Citizen::SetTarget(Plot* t)
{
    target = t;
} 

/**
 * \brief Handles all update events of the citizen
 */
void Citizen::Update()
{
    if (dead)
    {
        return;
    }
    
    UpdateRules();
    // Citizen is waiting in a target
    if (waitTime > 0)
    {
        waitTime -= CoreController::Instance()->GetDeltaTime();
        UpdateScreenCoordinates();
        return;
    }
    
    // Citizen has a target
    if (target != nullptr)
    {
        // Citizen has arrived at tempTarget
        if (tempTarget == coords)
        {
            coords = tempTarget;
            // Has arrived at final target or has no path
            if (path == nullptr || path->IsEmpty())
            {
                if (activeRule != nullptr)
                {
                    // Trigger rule enter
                    activeRule->EnterPlot(target);
                }
                // Trigger Plot enter
                target->Enter(this);
                inPlot = true;
                // Citizen is now in a plot and no longer has a target
                currentPlot = target;
                target = nullptr;
                return;
            }

            tempTarget = path->Pop();
            const auto curPlot = CoreController::GetSystemController()->Plots()->FindPlot(coords);
            const auto nextPlot = CoreController::GetSystemController()->Plots()->FindPlot(tempTarget);
            if (currentRoad != nullptr)
            {
                currentRoad->Leave();
            }
            currentRoad = curPlot->GetRoad(nextPlot);
            currentRoad->Enter();
            return;
        }
        
        // Citizen is heading toward target
        float speed = CoreController::Instance()->GetDeltaTime() * moveSpeed * currentRoad->Speed();
        if (doubleSpeedTime > 0)
        {
            doubleSpeedTime -= CoreController::Instance()->GetDeltaTime();
            speed *= 2;
        }
        coords = coords.MoveTowards(tempTarget, speed);
        UpdateScreenCoordinates();
        return;
    }
    
    // Citizen is leaving old target and finding next one;
    if (pathFindFailed)
    {
        pathFindFailed = false;
        FindNextTarget();
        return;
    }
        
    currentPlot->Leave(this);
    if(activeRule != nullptr)
    {
        activeRule->LeavePlot(currentPlot);
    }
    inPlot = false;
    coords = currentPlot->Coords();
    FindNextTarget();
}

void Citizen::UpdateScreenCoordinates()
{
    // Update coordinates;
    auto sCoords = coords.ToScreenCoordinates();
    sCoords.X -= 2.5;
    sCoords.Y -= 2.5;
    shape.setPosition(sCoords.X, sCoords.Y);
}


/**
 * \brief Set a time for the citizen to wait in the plot. 1 = ??? ingame minutes
 * \param time Time to wait for
 */
void Citizen::Wait(const float time)
{
    if (forceWait != 0)
    {
        waitTime = forceWait;
        forceWait = 0;
        return;
    }
    waitTime = time;
}

void Citizen::NewDay()
{
    switch (age)
    {
    case RETIREMENT_AGE:
        dynamic_cast<HomeRule*>(FindRule(HOME))->Unregister();
        dynamic_cast<WorkRule*>(FindRule(WORK))->UnRegister();
        break;
    case HOSPITALIZED_AGE:
        dynamic_cast<HospitalRule*>(FindRule(HOSPITAL))->Register();
        break;
    default:
        break;
    }
	for (auto&& rule : rules)
	{
		rule->NewDay();
	}
}

/**
 * \brief Handles end day events
 */
void Citizen::EndDay()
{
    age += 3;
	for (auto&& rule : rules)
	{
		rule->EndDay();
	}
}

/**
 * \brief Forces a citizen to do a specific rule for "waitTime" hours
 * \param ruleType Rule type being forced
 * \param waitTime Time to force the rule to run for
 */
void Citizen::ForceRule(const System ruleType, const float waitTime /* = 0 */ )
{
    FindRule(ruleType)->FindPlot();

    if (waitTime != 0)
    {
        forceWait = waitTime;
    }
}

/**
 * \brief Finds a rule of system type
 * \param system type of rule being searched for
 * \return The rule system
 */
BaseRule* Citizen::FindRule(const System system) const
{
    switch (system)
    {
    case FOOD:
    case WORK:
    case BANK: 
    case HOME: 
    case STORE: 
    case SCHOOL: 
    case HOSPITAL: 
        return rules[system - 1];    
    default: 
        return nullptr;
    }
}

bool Citizen::IsMarried() const
{
	return family[static_cast<int>(SPOUSE)] != nullptr;
}

/**
 * \brief Marries two people and sets their relationship to each other
 * \param spouse Citizen person in being married to
 */
void Citizen::Marry(Citizen * spouse)
{
	SetRelationships(SPOUSE, spouse);
	spouse->SetRelationships(SPOUSE, this);
}

/**
 * \brief Marks citizen as dead. Die pruning and events are handled at the end of day
 */
void Citizen::Die()
{
    dead = true;
    CoreController::GetSystemController()->Citizens()->NewDeath();
    auto hospital = dynamic_cast<HospitalSystem*>(CoreController::GetSystemController()->GetSystem(HOSPITAL));
    if (!dynamic_cast<HospitalRule*>(FindRule(HOSPITAL))->InHospital())
    {
        hospital->DeathOutside();
    }
    hospital->Death();
}

/**
 * \brief Calls the death events for each rule
 */
void Citizen::DeathEvents()
{
    if (currentPlot != nullptr)
    {
        currentPlot->Leave(this);
    }
    if (currentRoad != nullptr)
    {
        currentRoad->Leave();
    }
}

/**
 * \brief Finds the next target for the citizen based on rules, or random if none is available
 */
void Citizen::FindNextTarget()
{
    List<BaseRule*> skipRules;

    BaseRule* baseRule;
    do
    {
        baseRule = nullptr;
        float bestScore = 0;
        for (auto & rule : rules)
        {
            const auto tRule = rule;
            auto skip = false;
            for (auto && skipRule : skipRules)
            {
                if (skipRule == tRule)
                {
                    skip = true;
                    break;
                }
            }
        
            if (skip)  continue;
        
            const auto score = tRule->CalculateScore();
            if (score == 0) continue;
            
            if (baseRule == nullptr || score > bestScore)
            {
                bestScore = score;
                baseRule = rule;
            }
            
        }
        
        if (baseRule == nullptr || baseRule->FindPlot()) break;
        skipRules.InsertLast(baseRule);
    }
    while (baseRule != nullptr);
    // No rule satisfiable
    if (baseRule == nullptr)
    {
        activeRule = nullptr;
        FindRandomTarget();
    }
    else
    {
        FindPath();
    }
    // TODO : Head Home
    
}

/**
 * \brief Initializes citizen rules
 */
void Citizen::GenRules()
{
    // NONE,    FOOD,	WORK,	BANK,	HOME,	STORE, 	SCHOOL,    HOSPITAL
    BaseRule* food = new FoodRule(*this);
	BaseRule* work = new WorkRule(*this);
	BaseRule* bank = new BankRule(*this);
	BaseRule* home = new HomeRule(*this);
	BaseRule* store = new StoreRule(*this);
    BaseRule* school = new SchoolRule(*this);
    BaseRule* hospital = new HospitalRule(*this);
    
    rules.InsertLast(food);
	rules.InsertLast(work);
	rules.InsertLast(bank);
	rules.InsertLast(home);
	rules.InsertLast(store);
    rules.InsertLast(school);
    rules.InsertLast(hospital);
}

/**
 * \brief Finds a random target amongst neighbour plots
 */
void Citizen::FindRandomTarget()
{
    const auto neighbours = coords.GetNeighbours();

    do
    {
        target = CoreController::GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
    } while (target == nullptr || target->IsRiver());
    delete[] neighbours;
    FindPath();
}

/**
 * \brief Calls respective update events in rules
 */
void Citizen::UpdateRules() const
{
    for (auto && rule : rules)
    {
        rule->Update();
    }
}

/**
 * \brief Attempts to find a path to the target, if fails, sets pathFindFailed to true
 */
void Citizen::FindPath()
{
    delete path;
    path = PathFinder::PathTo(coords, target->Coords());
    // No path found
    if (path == nullptr)
    {
        target = nullptr;
        pathFindFailed = true;
        return;
    }
    
    tempTarget = path->Pop();
}

/**
 * \brief Sets up the relationship log of two citizens
 * \param relation Relationship relative to citizen
 * \param citizen Other citizen setting relationships
 */
void Citizen::SetRelationships(const Relationship& relation,Citizen * citizen)
{
	family[static_cast<int>(relation)] = citizen;
}
