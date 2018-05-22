#include "FoodSystem.h"
#include "Food.h"



FoodSystem::FoodSystem() : BaseSystem(FOOD)
{
}


FoodSystem::~FoodSystem()
= default;

void FoodSystem::Register(Plot* plot)
{
    (*plot).Register(new Food(plot));
    BaseSystem::Register(plot);
}

void FoodSystem::Update(float deltaTime)
{
    
}
