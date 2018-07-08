#pragma once
#include "../Base/Base.h"

/**
* \brief Store Class that handles the store plots of our city
*/
class Store : public Base
{
friend StoreSystem;
friend StoreRule;

public:
	Store(Plot* plot);
	~Store();
	
	void EndDay() override;
    void NewDay() override;
    std::string ContentString() override;
private:
    static const int CROWDED;
    static const int OPERATING_COST;
    
    void Enter();
    void Payment(float money);
    
    int cleaningCost = 0;
    int crowdedCount = 0;
    int mostCustomer = 0;
    int earnings = 0;
};

