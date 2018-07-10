#pragma once
#include "../Base/BaseSystem.h"


class WorkSystem :  public BaseSystem
{
	friend class Work;
	friend class WorkRule;
public:
    WorkSystem();
    ~WorkSystem();

	int Register(Plot* plot) override;
	void Unregister(Plot* plot) override;
	void Update() override;
	float GetSatisfaction() const override;
	void EndDay() override;
	void Toggle() override;
    int Cost() const override;
	std::string ContentString() override;
private:
	bool highLevel;
    const int cost[2] = {3000,5000};
	LinkedList<Plot*> highWork;
	LinkedList<Plot*> lowWork;
};


