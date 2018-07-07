#pragma once
#include "../Base/BaseSystem.h"

/**
 * \brief Hospital systems that tracks and handles collective food plots and events
 */
class HospitalSystem : public BaseSystem
{
public:
    HospitalSystem();
    ~HospitalSystem();
    int Register(Plot* plot) override;
    float GetSatisfaction() const override;
    void Update() override;
    void DeathOutside();
    void Death();
    void NewDay() override;
    void EndDay() override;
    std::string ContentString() override;
private :
    const int maxOccupantCount = 20;
    const int scorePerOccupant = 10;
    const int overPenalty = 5;
    
    int unhappyDeath = 0;
    int totalDeaths = 0;
};

