#include "FoodRule.hpp"
#include "Food.hpp"

#include "../Base/BaseSystem.h"
#include "../../Collections/List.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"

helper::Time FoodRule::breakfastTime;
helper::Time FoodRule::lunchTime;

FoodRule::FoodRule(Citizen& citizen): BaseRule(citizen, FOOD), hungerLevel(100) { }

FoodRule::~FoodRule() = default;

float FoodRule::CalculateScore()
{
    if (hungerLevel > 80 || citizen->Money() < MAX_FOOD_COST)
    {
        return 0;
    }
    return Clamp(exp((80 - hungerLevel)/4), 0.f, INFINITY - 5000);
}

/**
 * \brief Attemps to find a plot that can satisfy this rule
 * \return True if successfully found a plot to satisfy rule, otherwise false
 */
bool FoodRule::FindPlot()
{
    auto& plots = CoreController::GetSystemController()->GetSystem(FOOD)->Plots();

    // Get a list of plots that fulfill out requirements ( distance < max distance
    List<Plot*> choices;
    auto coords = citizen->Coords();
    for (auto&& plot : plots)
    {
        if (!Pathable(coords, plot->Coords())) continue;
        const auto distance = plot->Coords().Distance(coords);
        if (distance < maxDistance)
        {
            auto p = plot;
            choices.InsertLast(p);
        }
    }

    // If such a list doesn't exist. This rule returns failed result false
    if (choices.Count() == 0)
    {
        return false;
    }
    const auto chosen = choices[RandomInt(0, choices.Count())];
    citizen->SetActiveRule(this);
    citizen->SetTarget(chosen);

    return true;
}

void FoodRule::EnterPlot(Plot* plot)
{
    const auto food = dynamic_cast<Food*>(plot->GetPlotType());
    if (food == nullptr) return;
    food->Enter();
    float wait;
    const auto& time = CoreController::Instance()->GetTime();
    if (time < breakfastTime)
    {
        wait = 0.3f;
    }
    else if(time < lunchTime)
    {
        wait = 0.6f;
    }
    else
    {
        wait = 0.8f;
    }
    
    citizen->Wait(wait);
    // TODO : Move base enter to plot
}

/**
 * \brief Fills up the citizen's hunger on leaving
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void FoodRule::LeavePlot(Plot* plot)
{
    const auto& time = CoreController::Instance()->GetTime();
    int fill;
    if (time < breakfastTime)
    {
        fill = 20;
    }
    else if(time < lunchTime)
    {
        fill = 40;
    }
    else
    {
        fill = 60;
    }
    hungerLevel = Clamp(hungerLevel + fill, 0.f, 100.f);
}

/**
 * \brief Update events of food rule. Decreases citizen's hunger
 */
void FoodRule::Update()
{
    // TODO : Tweak hunger to time ratio
    // Right now people die roughly in two without eating
    // Or will have the urge to eat about every 6 hours (small urge) (exponential growth).
    hungerLevel -= CoreController::Instance()->GetDeltaTime() * 3;
    if (hungerLevel < 0)
    {
        citizen->Die();
    }
}

/** 
 * \brief Used to fill hunger before entering hospital 
 */
void FoodRule::FillHunger(const float hunger /* = INT_MAX */ )
{
    hungerLevel = hunger;
} 