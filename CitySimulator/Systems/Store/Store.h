#pragma once
#include "..\Base\Base.h"

class StoreRule;

/**
* \brief Store Class that handles the store plots of our city
*/
class Store :	public Base
{
friend StoreRule;

public:
	Store(Plot* plot);
	~Store();
	
	void EndDay() override;

private:
	int cost;

	void Enter();
};

