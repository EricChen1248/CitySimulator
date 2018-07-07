#pragma once
#include "../Base/Base.h"
#include "Bank.h"
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
	std::string ContentString() override;
	void NewDay() override;
	void EndDay() override;
private:
	int cost;
	int transactionCost;
	int administrationFee;
	int earnedMoeny;
	int customerPerDay;
	void Enter();
	
};

