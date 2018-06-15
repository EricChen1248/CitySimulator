#pragma once
#include "../Base/Base.h"

class FoodRule;

/**
 * \brief Food Class that handles the food plots of our city
 */
class Food : public Base
{
friend FoodRule;

    public:
    Food(Plot* plot);
    ~Food() = default;
    void EndDay() override;
private:
    int cost;
    
    void Enter();
};

