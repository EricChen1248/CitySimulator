#pragma once
#include "../Base/BaseSystem.h"


class WorkSystem :  public BaseSystem
{
	friend class Work;
public:
    WorkSystem();
    ~WorkSystem();

	int Register(Plot* plot) override;
	void Update() override;
	float GetSatisfaction() const override;
	void EndDay() override;
	void Toggle() override;
    int Cost() const override;
	std::string ContentString() override;
private:
	bool highLevel;
    const int cost[2] = {500,1000};
};


