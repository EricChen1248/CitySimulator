#pragma once
#include "../Base/Base.h"

class FoodRule;

class Food : public Base
{
friend FoodRule;

    public:
    Food(Plot* plot);
    ~Food() = default;
    void Reset() override;
private:
    int cost;
    int earnings;
    
    void Enter();
};

