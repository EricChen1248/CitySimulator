#pragma once
#include "../Base/BaseRule.h"
#include "../Base/Base.h"
#include "Home.h"
class BaseRule;

/**
* \brief Food rule that handles the food needs of our citizens
*/
class HomeRule : public BaseRule
{
public:
	HomeRule(Citizen& citizen);;
	~HomeRule();

	float CalculateScore();
	bool FindPlot();
	void EnterPlot(Plot* plot);
	void LeavePlot(Plot* plot);
	void Update();
	bool IsSatisfied() override;
private:
	// TODO : Tweak foodrule max distance
	const int maxDistance = 20;
	Home* myHome;
	int homelessLevel;
	float homelessHour;
};

