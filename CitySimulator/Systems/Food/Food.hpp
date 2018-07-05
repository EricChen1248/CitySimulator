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
    static const int MAX_FOOD_COST = 100;
private:
    const int maxCustomer = 10;
    int cost;
    int earnedMoney;
    int overloadedTally;
    
    void Enter();
};

