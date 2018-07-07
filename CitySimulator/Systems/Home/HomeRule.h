#pragma once
#include "../Base/BaseRule.h"
#include "Home.h"
#include "../Citizen/Citizen.h"
#include "../../Helpers/Time.h"
class BaseRule;

/**
* \brief Food rule that handles the food needs of our citizens
*/
class HomeRule : public BaseRule
{
public:
	friend Home;
	HomeRule(Citizen& citizen);;
	~HomeRule();

	float CalculateScore() override;
	bool FindPlot() override;
	void EnterPlot(Plot* plot) override;
	void LeavePlot(Plot* plot) override;
	void Update() override;
	void EndDay() override;
	void Unregister();
	bool HasHome()const { return (myHome != nullptr); };
	bool AtHome()const { return atHomeFlag; };
	Home* GetHome()const { return myHome; }
	float GetSleepTime()const;
private:

	helper::Time goHomeTime;
	helper::Time atHomeTime;
	helper::Time wakeUpTime;
	bool DecideHome();
	Home* myHome;
	int homelessLevel;
	float sleepingHour;
	bool atHomeFlag;
};

