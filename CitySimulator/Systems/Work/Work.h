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

	void NewEmployee(Citizen* citizen);
	void Resignation(Citizen* citizen);

private:
	void Enter(const float workingTime, const float production);

	int todayEmployee;
	int todayLateEmployee;
	float baseSalary;
	float production;
	float todayWorkingTime;
	List<Citizen*> employees;
	bool highLevel;
};


