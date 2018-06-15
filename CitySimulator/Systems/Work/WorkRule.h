#pragma once
#include "../Base/BaseRule.h"
#include "Work.h"
#include "../../Helpers/Time.h"


class BaseRule;
/**
* \brief Work rule that handles the food needs of our citizens
*/
class WorkRule : public BaseRule
{
	friend class WorkSystem;
public:
    WorkRule(Citizen& citizen);
    ~WorkRule();
private:
	const int maxDistance = 10;
	Plot* assignedCompany;
	float production;
	float salary;

	static helper::Time timeToWork;
	static helper::Time breakTime;
	static helper::Time endBreakTime;
	static helper::Time timeOffWork;

	float CalculateScore();
	bool FindPlot();
	void EnterPlot(Plot* plot);
	void LeavePlot(Plot* plot);
	void Update();
	bool IsSatisfied() override;
};