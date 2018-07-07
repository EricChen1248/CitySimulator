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
    if (hungerLevel > 80 || citizen->GetMoney() < MAX_FOOD_COST)
    {
        return 0;
    }
    return exp(80 - hungerLevel) * 1000;
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
    for (auto&& plot : plots)
    {
        auto coords = citizen->Coords();
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
    hungerLevel -= CoreController::Instance()->GetDeltaTime() * 3;
    if (hungerLevel < 0)
    {
        citizen->Die();
    }
}

/** 
 * \brief Used to fill hunger before entering hospital 
 */
void FoodRule::FillHunger(const float hunger)
{
    hungerLevel = hunger;
} 