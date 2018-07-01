#pragma once
#include "../Base/BaseSystem.h"

/**
 * \brief Food systems that tracks and handles collective food plots and events
 */
class FoodSystem : public BaseSystem
{
public:
    FoodSystem();
    ~FoodSystem();
    void Register(Plot* plot) override;
    void Update() override;
    void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
    void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
    float GetSatisfaction() const override;
private :
    const int maxOccupantCount = 20;
    const int scorePerOccupant = 10;
    const int overPenalty = 5;
};

