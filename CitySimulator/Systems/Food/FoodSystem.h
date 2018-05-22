#pragma once
#include "../Base/BaseSystem.h"
class FoodSystem :
    public BaseSystem
{
public:
    FoodSystem();
    ~FoodSystem();
    void Register(Plot* plot);
    void Update(float deltaTime);
};

