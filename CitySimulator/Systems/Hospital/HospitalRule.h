#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
 * \brief Hospital rule that handles the food needs of our citizens
 */
class HospitalRule : public BaseRule
{
public:
    HospitalRule(Citizen& citizen);;
    ~HospitalRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
	void EndDay() override;
    
    bool InHospital() const { return assignedHospital != nullptr; }
	void Register();

private:
    const int deltaIncrease = 5;
	Plot* assignedHospital;
    bool enter = false; 
};

