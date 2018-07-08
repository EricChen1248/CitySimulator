#pragma once
#include "../Base/BaseRule.h"

/**
* \brief Store rule that handles the consumption needs of our citizens
*/
class StoreRule : public BaseRule
{
public:
	 StoreRule(Citizen& citizen);;
    ~StoreRule();

    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
private:
	const int maxDistance = 100;
    
    float foodStock;
    float miscStock;
    float householdStock;
    
    static const float MAX_STOCK;
    static const float RESTOCK;
    static const float FOOD_COST;
    static const float HOUSE_COST;
    static const float MISC_COST;
    
};

