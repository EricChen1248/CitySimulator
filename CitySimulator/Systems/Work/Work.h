#pragma once
#include "../Base/Base.h"

class WorkRule;

class Work : Base
{
	friend class WorkRule;

public:
	Work(Plot* plot);
	~Work() = default;
	void Reset() override;
private:
	void Enter();
	int production;
	int salary;
};
