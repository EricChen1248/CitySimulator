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
    bool IsSatisfied() override;

	void Register();

private:
    const int maxDistance = 10;
	Plot* assignedHospital;
    bool enter = false; 
};

