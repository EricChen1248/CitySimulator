#pragma once
#include "../Base/Base.h"
#include "Bank.h"

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
	int MoneyEarned() const { return earnedMoney; };
	int CustomerCount() const { return customerPerDay; };
private:
	int transactionCost;
	int administrationFee;
	int earnedMoney;
	int customerPerDay;
	int countOfCustomerNow;
	void Enter();
};

