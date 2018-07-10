#pragma once
#include "../Base/BaseSystem.h"

/**
 * \brief Hospital systems that tracks and handles collective food plots and events
 */
class HospitalSystem : public BaseSystem
{
    friend class HospitalRule;
public:
    HospitalSystem();
    ~HospitalSystem();
    int Register(Plot* plot) override;
    float GetSatisfaction() const override;
    void Update() override {};
    void DeathOutside();
    void Death();
    void NewDay() override;
    void EndDay() override;
    std::string ContentString() override;
	int Cost() const override { return 6000; }


private :	
	float crowdedScoreMinus = 0.f;
	int crowdedHospital = 0;
    int unhappyDeath = 0;
    int totalDeaths = 0;
    
    float satisfactionToday = 0;
};

