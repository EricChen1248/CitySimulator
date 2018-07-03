#include "FoodRule.hpp"
#include "Food.hpp"

#include "../../Controllers/CoreController.h"
#include "../../Helpers/HelperFunctions.h"

helper::Time FoodRule::breakfastTime;
helper::Time FoodRule::lunchTime;
helper::Time FoodRule::dinnerTime;

FoodRule::FoodRule(Citizen& citizen): BaseRule(citizen, FOOD), hungerLevel(0) { }

FoodRule::~FoodRule() = default;

float FoodRule::CalculateScore()
{
    if (hungerLevel > 80)
    {
        return 0;
    }
    return exp(100 - hungerLevel) * 1000;
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
    const auto& time = CoreController::Instance()->GetTime();
    citizen->Wait(1.f);
    citizen->IncreaseMoney(-food->cost);
    food->Enter();
}

/**
 * \brief Fills up the citizen's hunger on leaving
 * \param plot Plot thats is being left. Redudant. Only for interface requirements
 */
void FoodRule::LeavePlot(Plot* plot)
{
    hungerLevel = 100.f;
}

/**
 * \brief Update events of food rule. Decreases citizen's hunger
 */
void FoodRule::Update()
{
    // TODO : Tweak hunger to time ratio
    hungerLevel -= CoreController::Instance()->GetDeltaTime() * 72;
}

/**
 * \brief Returns bool to tell if citizen is satisfied with it's food requirements
 * \return True if hunger level is over 20
 */
bool FoodRule::IsSatisfied()
{
    return hungerLevel > 20;
}

/** 
 * \brief Used to fill hunger before entering hospital 
 */
void FoodRule::FillHunger()
{
    hungerLevel = std::numeric_limits<float>::max();;
} 