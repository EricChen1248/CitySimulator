#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
 * \brief Food rule that handles the food needs of our citizens
 */
class FoodRule : public BaseRule
{
friend class Food;
friend class FoodSystem;
public:
    FoodRule(Citizen& citizen);
    ~FoodRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
    
    float Hunger() const { return hungerLevel; }
    void FillHunger(float hunger = std::numeric_limits<float>::max());
private:
    static const int MAX_FOOD_COST = 100;
    static helper::Time breakfastTime;
    static helper::Time lunchTime;
    
    // TODO : Tweak foodrule max distance
    const int maxDistance = 10;
    float hungerLevel;
};

