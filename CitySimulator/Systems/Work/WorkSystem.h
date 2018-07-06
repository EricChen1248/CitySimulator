#pragma once
#include "../Base/BaseSystem.h"


class WorkSystem :  public BaseSystem
{
public:
    WorkSystem();
    ~WorkSystem();

	int Register(Plot* plot);
	void Update();
	float GetSatisfaction() const;
	void LogSatisfied(Citizen* citizen, BaseRule* rule);
	void LogUnsatisfied(Citizen* citizen, BaseRule* rule);
	void EndDay();
	void Toggle();
};


