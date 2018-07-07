#pragma once
#include "../Base/BaseSystem.h"


class WorkSystem :  public BaseSystem
{
	friend class Work;
public:
    WorkSystem();
    ~WorkSystem();

	int Register(Plot* plot);
	void Update();
	float GetSatisfaction() const;
	void EndDay();
	void Toggle();
	std::string ContentString();
private:
	bool highLevel;
};


