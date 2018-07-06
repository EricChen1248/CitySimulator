#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
 * \brief School rule that handles the food needs of our citizens
 */
class SchoolRule : public BaseRule
{
public:
    SchoolRule(Citizen& citizen);
    ~SchoolRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
    bool IsSatisfied() override;
	float EducationLevel() const { return educationLevel; };
private:
	float educationLevel;
};

