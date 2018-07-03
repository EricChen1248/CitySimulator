#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
 * \brief Food rule that handles the food needs of our citizens
 */
class FoodRule : public BaseRule
{
friend class FoodSystem;
    
public:
    FoodRule(Citizen& citizen);
    ~FoodRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
    bool IsSatisfied() override;
    
    void FillHunger();
private:
    static helper::Time breakfastTime;
    static helper::Time lunchTime;
    static helper::Time dinnerTime;
    
    // TODO : Tweak foodrule max distance
    const int maxDistance = 10;
    float hungerLevel;
};

