#pragma once
#include "../Base/BaseRule.h"
#include "../Plot/Plot.h"

class BaseRule;
class FoodRule :
    public BaseRule
{
public:
    FoodRule(Citizen& citizen);;
    ~FoodRule();

    float CalculateScore();
    bool FindPlot();
    void EnterPlot();
    void LeavePlot();
    void Update();
private:
    // TODO : Tweak foodrule max distance
    const int maxDistance = 10;
    float hungerLevel;
};

