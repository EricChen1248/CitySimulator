#pragma once
#include "../Base/Base.h"
class Work :¡@public Base
{
	friend WorkRule;

public:
	Work(Plot* plot);
	~Work() = default;
	void Reset() override;
private:
	int earnings;
	int cost;

	void Enter();
};
