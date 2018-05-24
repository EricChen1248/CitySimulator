#include "FoodRule.h"
#include "../../Controllers/CoreController.h"
#include "FoodSystem.h"
#include "Food.h"

FoodRule::FoodRule(Citizen& citizen): BaseRule(citizen), hungerLevel(0)
{
}

FoodRule::~FoodRule() = default;

float FoodRule::CalculateScore()
{
    if (hungerLevel > 80)
    {
        return 0;
    }
    return (100 - hungerLevel) * 100;
}

/**
 * \brief Attemps to find a plot that can satisfy this rule
 * \return True if successfully found a plot to satisfy rule, otherwise false
 */
bool FoodRule::FindPlot()
{
    auto &plots = CoreController::Instance()->GetSystemController()->GetSystem(FOOD)->Plots();
    
    // Get a list of plots that fulfill out requirements ( distance < max distance
    List<Plot*> choices;
    for (int i = 0; i < plots.Count(); ++i)
    {
        auto plot = plots[i];
        auto coords = citizen->Coords();
        const auto distance = plot->Coords().Distance(coords);
        if (distance < maxDistance)
        {
            choices.InsertLast(plot);
        }
    }
    
    // If such a list doesn't exist. This rule returns failed result false
    if (choices.Count() == 0)
    {
        return false;
    }
    const auto chosen = choices[CoreController::RandomInt(0, choices.Count())];
    citizen->SetActiveRule(this);
    citizen->SetTarget(chosen);
    
    return true;
}

void FoodRule::EnterPlot(Plot* plot)
{
    const auto food = dynamic_cast<Food*>(plot->GetPlotType());
    citizen->Wait(1.f);
    citizen->IncreaseMoney(-food->cost);
    food->Enter();
}

void FoodRule::LeavePlot(Plot* plot)
{
    hungerLevel = 100.f;
}

void FoodRule::Update()
{
    // TODO : Tweak hunger to time ratio
    this->hungerLevel -= CoreController::Instance()->GetDeltaTime() * 30;
}
