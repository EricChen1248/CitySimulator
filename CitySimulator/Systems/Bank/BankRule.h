#pragma once
#include "../Base/BaseRule.h"
#include "../Bank/Bank.h"
class BaseRule;

/**
* \brief Food rule that handles the food needs of our citizens
*/
class BankRule : public BaseRule
{
public:
	BankRule(Citizen& citizen);
	~BankRule();

	float CalculateScore() override;
	bool FindPlot() override;
	void EnterPlot(Plot* plot) override;
	void LeavePlot(Plot* plot) override;
	void Update() override;
	void SaveMoney(float moneyInflow);
    int GetSavings() const { return int(saving); }
private:
	float saving;
	float moneyDownLimit;
};

