#include "FoodRule.h"
#include "../../Controllers/CoreController.h"


FoodRule::FoodRule(Citizen& citizen): BaseRule(citizen), hungerLevel(0)
{
}

FoodRule::~FoodRule() = default;

float FoodRule::CalculateScore()
{
    return hungerLevel * 100;
}

void FoodRule::EnterPlot()
{
    //TODO : Do something on enter
}

void FoodRule::LeavePlot()
{
}

void FoodRule::Update()
{
    this->hungerLevel += lastUpdate - CoreController::Instance()->GetTime();
}
