#include <cstdlib>
#include "Citizen.h"
#include "../Food/FoodRule.h"
#include "../Bank/BankRule.h"
#include "../Work/WorkRule.h"
#include "../Home/HomeRule.h"
#include "../Store/StoreRule.h" 
#include "../School/SchoolRule.h" 
#include "../Hospital/HospitalRule.h" 
#include "../../Controllers/CoreController.h"
#include "../../Helpers/PathFinder/PathFinder.h"
#include "../../Helpers/HelperFunctions.h"


Citizen::Citizen(Plot* plot) : target(nullptr), activeRule(nullptr), coords(plot->Coords()), money(0), waitTime(0.f), inPlot(false), dead(false), age(0)
{
    moveSpeed = 1 + static_cast<float>(RandomInt(0, 40) - 20) / 100;
    shape = sf::CircleShape(5);
    shape.setFillColor(BLUE);
    currentPlot = plot;
    
    GenRules();
}


Citizen::~Citizen() = default;


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
            // Has arrived at final target
            if (path->IsEmpty())
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
            return;
        }
        
        // TODO add road movement speed
        // Citizen is heading toward target
        coords = coords.MoveTowards(tempTarget, CoreController::Instance()->GetDeltaTime() * moveSpeed);
        UpdateScreenCoordinates();
        return;
    }
    
    // Citizen is leaving old target and finding next one;
    UpdateRules();
    currentPlot->Leave(this);
    if(activeRule != nullptr)
    {
        activeRule->LeavePlot(currentPlot);
        activeRule = nullptr;
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
    sCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    shape.setPosition(sCoords.X, sCoords.Y);
}


/**
 * \brief Set a time for the citizen to wait in the plot. 1 = ??? ingame minutes
 * \param time Time to wait for
 */
void Citizen::Wait(const float time)
{
    waitTime = time;
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
void Citizen::ForceRule(const System ruleType, const float waitTime)
{
    for (auto && rule : rules)
    {
        if (rule->Type() == ruleType)
        {
            rule->FindPlot();
        }
    }

    if (waitTime != 0)
    {
        Wait(waitTime);
    }
}

/**
 * \brief Finds a rule of system type
 * \param system type of rule being searched for
 * \return The rule system
 */
BaseRule* Citizen::FindRule(const System system)
{
    for (auto && rule : rules)
    {
        if (rule->Type() == system)
        {
            return rule;
        }
    }
    return nullptr;
    
}

/**
 * \brief Marks citizen as dead. Death pruning and events are handled at the end of day
 */
void Citizen::Death()
{
    dead = true;
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
        
            if (skip)
            {
                continue;
            }
        
            const auto score = tRule->CalculateScore();
            if (score == 0)
            {
                continue;
            }
            
            if (baseRule == nullptr || score > bestScore)
            {
                bestScore = score;
                baseRule = rule;
            }
            
        }
        
        if (baseRule == nullptr || baseRule->FindPlot())
        {
            break;
        }
        skipRules.InsertLast(baseRule);
    }
    while (baseRule != nullptr);
    // No rule satisfiable
    if (baseRule == nullptr)
    {
        ++unsatisfiedCount;
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
	rules.InsertLast(bank);
	rules.InsertLast(work);
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
        target = CoreController::Instance()->GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
    } while (target == nullptr);
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

void Citizen::FindPath()
{
    delete path;
    path = PathFinder::PathTo(coords, target->Coords());
    tempTarget = path->Pop();
}
