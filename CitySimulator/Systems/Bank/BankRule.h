#pragma once
#include "../Base/BaseRule.h"

class BaseRule;

/**
* \brief Food rule that handles the food needs of our citizens
*/
class BankRule : public BaseRule
{
public:
	BankRule(Citizen& citizen);;
	~BankRule();

	float CalculateScore();
	bool FindPlot();
	void EnterPlot(Plot* plot);
	void LeavePlot(Plot* plot);
	void Update();
	bool IsSatisfied() override;
private:
	// TODO : Tweak foodrule max distance
	const int maxDistance = 20;
	float saving;
};

