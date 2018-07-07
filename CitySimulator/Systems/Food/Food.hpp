#pragma once
#include "../Base/Base.h"

class FoodRule;
/**
 * \brief Food Class that handles the food plots of our city
 */
class Food : public Base
{
friend class FoodSystem;
friend class FoodRule;

public:
    Food(Plot* plot);
    ~Food();
    std::string ContentString() override;
    
    void NewDay() override;
    void EndDay() override { };
    int FoodCost(const helper::Time& time) const;
private:
    const int maxCustomer = 10;
    static const int MEAL_COST[3] ;
    int mealDeltaCost;
    int earnedMoney;
    int overloadedTally;
    
    void Enter();
};

