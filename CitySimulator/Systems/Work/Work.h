#pragma once
#include "../Base/Base.h"
#include "WorkRule.h"

class Work : Base
{
	friend class WorkRule;

public:
	Work(Plot* plot);
	~Work() = default;
	void Reset() override;
private:
	void Enter();
};
