#include <cstdlib>
#include "Citizen.h"
#include "../../Controllers/CoreController.h"
#include "../Food/FoodRule.h"


Citizen::Citizen(Plot* plot) : target(nullptr), activeRule(nullptr), coords(plot->Coords()), money(0), waitTime(0.f), inPlot(false)
{
    moveSpeed = 1 + static_cast<float>(CoreController::RandomInt(0, 40) - 20) / 100;
    shape = CircleShape(5);
    shape.setFillColor(Color::Blue);
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
    
    // TODO : Path to target
} 

/**
 * \brief Handles all update events of the citizen
 * \param deltaTime Time since prev update
 */
void Citizen::Update(const float deltaTime)
{
    // Citizen is waiting in a target
    if (waitTime > 0)
    {
        waitTime -= deltaTime;
        return;
    }
    // Citizen has a target
    if (target != nullptr)
    {
        // Citizen has arrived at target
        if (target->Coords() == coords)
        {
            // Is wandering
            if (activeRule != nullptr)
            {
                activeRule->EnterPlot();
            }
            target->Enter(this);
            inPlot = true;
            
            // Citizen is now in a plot and no longer has a target
            currentPlot = target;
            target = nullptr;
            return;
        }
        
        // Citizen is heading toward target
        coords = coords.MoveTowards(target->Coords(), deltaTime * moveSpeed);
        
        // Update coordinates;
        auto sCoords = coords.ToScreenCoordinates();
        sCoords.X -= 2.5;
        sCoords.Y -= 2.5;
        sCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    
        shape.setPosition(sCoords.X, sCoords.Y);
        return;
    }
    
    // Citizen is leaving old target and finding next one;
    UpdateRules();
    currentPlot->Leave(this);
    inPlot = false;
    coords = currentPlot->Coords();
    FindNextTarget();
}


/**
 * \brief Set a time for the citizen to wait in the plot
 * \param time Time to wait for
 */
void Citizen::Wait(const float time)
{
    waitTime = time;
}

CircleShape& Citizen::GetShape()
{
    return shape;
}

void Citizen::FindNextTarget()
{
    List<BaseRule*> skipRules;

    BaseRule* rule;
    do
    {
        rule = nullptr;
        float bestScore = 0;
        for (int i = 0; i < rules.Count(); ++i)
        {
            const auto tRule = rules[i];
            auto skip = false;
            for (int j = 0; j < skipRules.Count(); ++j)
            {
                if (skipRules[j] == tRule)
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
            if (rule == nullptr || score > bestScore)
            {
                bestScore = score;
                rule = rules[i];
            }
        }
        
        if (rule == nullptr || rule->FindPlot())
        {
            break;
        }
        skipRules.InsertLast(rule);
    }
    while (rule != nullptr);
    if (rule == nullptr)
    {
        ++unsatisfiedCount;
        FindRandomTarget();
    }
    // TODO : Head Home
    
}

void Citizen::GenRules()
{
    BaseRule* food = new FoodRule(*this);
    rules.InsertLast(food);
   
}

void Citizen::FindRandomTarget()
{
    const auto neighbours = coords.GetNeighbours();

    do
    {
        target = CoreController::Instance()->GetSystemController()->Plots()->FindPlot(neighbours[rand() % 6]);
    } while (target == nullptr);
    delete[] neighbours;
}

void Citizen::UpdateRules() const
{
    for (int i = 0; i < rules.Count(); ++i)
    {
        rules[i]->Update();
    }
}
