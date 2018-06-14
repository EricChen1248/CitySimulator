#pragma once
#include "c:\Users\David Li\Documents\GitHub\CitySimulator\CitySimulator\Systems\Base\Base.h"

class StoreRule;

/**
* \brief Store Class that handles the store plots of our city
*/
class Store :	public Base
{
friend StoreRule;

public:
	Store();
	~Store();
	
	void EndDay() override;

private:
	int cost;

	void Enter();
};

