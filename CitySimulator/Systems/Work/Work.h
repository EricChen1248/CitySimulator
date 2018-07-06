#pragma once
#include "../Base/Base.h"

class WorkRule;

class Work : public Base
{
	friend class WorkRule;
	friend class WorkSystem;

public:
	Work(Plot* plot);
	~Work() = default;
	void EndDay() override;
	void NewDay() override;
	int Destroy() override;
	std::string ContentString() override;

	void NewEmployee();
	void Resignation();

private:
	void Enter(const float workingTime, const float production);
	int employeeCount;
	float todayWorkTime;
	float baseSalary;
};


