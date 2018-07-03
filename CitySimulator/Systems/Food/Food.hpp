#pragma once
#include "../Base/Base.h"
#include "../../Helpers/Time.h"

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
    void EndDay() override;
private:
    const int maxCustomer = 10;
    int cost;
    int customerCountTally;
    int overloadedTally;
    
    void Enter();
};

