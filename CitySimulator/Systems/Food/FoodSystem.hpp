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
    int Register(Plot* plot) override;
    void Update() override;
    void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
    void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
    float GetSatisfaction() const override;
    static const int OPERATING_COST = 1000;
private :
};

