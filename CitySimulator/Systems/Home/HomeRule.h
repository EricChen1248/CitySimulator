#pragma once
#include "../Base/BaseRule.h"
#include "../Base/Base.h"
#include "Home.h"
#include "../../Helpers/Time.h"
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
	void AfterGrowUp();
private:

	helper::Time goHomeTime;
	bool DecideHome();
	Home* myHome;
	int homelessLevel;
	float homelessHour;
};

