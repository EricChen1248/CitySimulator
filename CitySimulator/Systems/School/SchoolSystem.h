#pragma once
#include "../Base/BaseSystem.h"

/**
 * \brief School systems that tracks and handles collective food plots and events
 */
class SchoolSystem : public BaseSystem
{
public:
    SchoolSystem();
    ~SchoolSystem();
    void Register(Plot* plot) override;
    void Update() override;
    void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
    void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
    void ResetDay() override;
private :
    const int maxOccupantCount = 20;
    const int scorePerOccupant = 10;
    const int overPenalty = 5;
};

