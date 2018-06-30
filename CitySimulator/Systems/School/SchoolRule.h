#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
 * \brief School rule that handles the food needs of our citizens
 */
class SchoolRule : public BaseRule
{
public:
    SchoolRule(Citizen& citizen);;
    ~SchoolRule();

    float CalculateScore();
    bool FindPlot();
    void EnterPlot(Plot* plot);
    void LeavePlot(Plot* plot);
    void Update();
    bool IsSatisfied() override;
	int getEdLvl();
private:
	float EdLvl;
};

