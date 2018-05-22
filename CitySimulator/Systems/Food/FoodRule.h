#pragma once
#include "../Base/BaseRule.h"
#include "../Plot/Plot.h"

class FoodRule :
    public BaseRule
{
public:
    FoodRule(Citizen& citizen);;
    ~FoodRule();


    float CalculateScore();
    void EnterPlot();
    void LeavePlot();
private:
    void Update();
    float hungerLevel;
};

