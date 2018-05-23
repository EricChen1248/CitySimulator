#pragma once
#include "../Base/BaseSystem.h"
class FoodSystem :
    public BaseSystem
{
public:
    FoodSystem();
    ~FoodSystem();
    void Register(Plot* plot) override;
    void Update(float deltaTime) override;
    void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
    void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
    void ResetDay() override;
private :
    const int maxOccupantCount = 20;
    const int scorePerOccupant = 10;
    const int overPenalty = 5;
};

