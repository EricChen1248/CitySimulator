#pragma once
#include "../Base/Base.h"

class WorkRule;

class Work : public Base
{
	friend class WorkRule;

public:
	Work(Plot* plot);
	~Work() = default;
	void EndDay() override;
private:
	void Enter(float productDelta);

	float baseSalary;
};