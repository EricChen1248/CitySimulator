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

	static const int MAX_WORK_COST = 100;

private:
	void Enter(const float workingTime, const float production);

	int cost;
	int todayEmployee;
	int todayEarlyEmployee;
	int todayLateEmployee;
	float todayWorkTime;
	float baseSalary;
	float production;
	List<Citizen*> employees;
};


