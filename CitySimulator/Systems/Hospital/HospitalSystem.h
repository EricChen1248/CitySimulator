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
    void Update() override;
    void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
    void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
    void EndDay() override;
private :
    const int maxOccupantCount = 20;
    const int scorePerOccupant = 10;
    const int overPenalty = 5;
};

