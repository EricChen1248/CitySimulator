#pragma once
#include "../Base/Base.h"

class BankRule;

/**
* \brief Food Class that handles the food plots of our city
*/
class Bank : public Base
{
	friend BankRule;

public:
	Bank(Plot* plot);
	~Bank() = default;
	void EndDay() override;
private:
	int cost;
	int transactionCost;
	int administrationFee;
	void Enter();
};

