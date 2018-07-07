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
	friend class Work;
	friend class WorkSystem;
public:
    WorkRule(Citizen& citizen);
    ~WorkRule();
	float CalculateScore() override;
	bool FindPlot() override;
	void EnterPlot(Plot* plot) override;
	void LeavePlot(Plot* plot) override;
	void Update() override;
	bool IsSatisfied() override;
	void NewDay() override;
	void Register();
	void UnRegister();

private:
	const int maxDistance = 10;
	Plot* assignedCompany;
	float salary;
	float baseSalary;
	float workingTime; // Workingtime during this period (MAX:4 hour)
	int earlyToWork; // how much time a person should go outside early (in minutes)

	static helper::Time timeToWork;
	static helper::Time breakTime;
	static helper::Time endBreakTime;
	static helper::Time timeOffWork;
};