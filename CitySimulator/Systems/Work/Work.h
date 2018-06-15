#pragma once
#include "../Base/Base.h"

class WorkRule;

class Work : Base
{
	friend class WorkRule;

public:
	Work(Plot* plot);
	~Work() = default;
	void EndDay() override;
private:
	void Enter(int productDelta);

};