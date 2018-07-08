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
    float GetSatisfaction() const override;
    int Cost() const override { return 500; }
    std::string ContentString() override;
    static const int OPERATING_COST = 1000;
private :
};

