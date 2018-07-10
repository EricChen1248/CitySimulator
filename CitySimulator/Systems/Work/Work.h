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
    
    bool IsFull() const;

	void NewEmployee(Citizen* citizen);
	void Resignation(Citizen* citizen);

private:
	void Enter(float workingTime, float production);

    int employeeLimit;
	int todayEmployee;
	int todayLateEmployee;
	float baseSalary;
	float production;
	float todayWorkingTime;
	List<Citizen*> employees;
	bool highLevel;
};


