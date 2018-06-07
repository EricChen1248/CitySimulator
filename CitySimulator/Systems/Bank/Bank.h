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
	void Reset() override;
private:
	int cost;

	void Enter();
};

