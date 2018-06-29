#pragma once
#include "../Base/Base.h"

class HospitalRule;

/**
 * \brief Hospital Class that handles the Hospital plots of our city
 */
class Hospital : public Base
{
friend HospitalRule;

    public:
    Hospital(Plot* plot);
    ~Hospital() = default;
    void EndDay() override;
private:
    int cost;
    int capacity; 
    int citizenCount; 
    
    void Enter();
};

