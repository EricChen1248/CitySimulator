#pragma once
#include "../Base/BaseSystem.h"


class WorkSystem :  public BaseSystem
{
public:
    WorkSystem();
    ~WorkSystem();

	int Register(Plot* plot);
	void Update();
	void LogSatisfied(Citizen* citizen, BaseRule* rule);
	void LogUnsatisfied(Citizen* citizen, BaseRule* rule);
	void EndDay();
};


