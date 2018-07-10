#pragma once
#include "../Base/BaseRule.h"
#include "School.h"

class BaseRule;

/**
 * \brief School rule that handles the educational needs of our citizens
 */
class SchoolRule : public BaseRule
{
	friend class School;
	friend class SchoolSystem;
public:
    SchoolRule(Citizen& citizen);
    ~SchoolRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;

	float EducationLevel() const { return educationLevel; };
	void Register();
	void UnRegister();
private:
	static helper::Time schoolStartTime;
	static helper::Time schoolEndTime;

	School* assignedSchool;
	bool previousIsPremium;
	float educationLevel;
	int earlyToSchool;//Time to wake up to go to school
};

