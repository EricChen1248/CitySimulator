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

    float CalculateScore();
    bool FindPlot();
    void EnterPlot(Plot* plot);
    void LeavePlot(Plot* plot);
    void Update();
    bool IsSatisfied() override;
private:
    const int maxDistance = 10;
    bool enter = false; 
};

