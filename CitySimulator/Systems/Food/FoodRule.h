#pragma once
#include "../Base/BaseRule.h"

class BaseRule;
class FoodRule :
    public BaseRule
{
public:
    FoodRule(Citizen& citizen);;
    ~FoodRule();

    float CalculateScore();
    bool FindPlot();
    void EnterPlot(Plot* plot);
    void LeavePlot(Plot* plot);
    void Update();
private:
    // TODO : Tweak foodrule max distance
    const int maxDistance = 10;
    float hungerLevel;
};

