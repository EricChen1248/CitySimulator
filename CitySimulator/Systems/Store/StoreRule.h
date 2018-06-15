#pragma once
#include "../Base/BaseRule.h"

/**
* \brief Store rule that handles the consumption needs of our citizens
*/
class StoreRule :	public BaseRule
{
public:
	 StoreRule(Citizen& citizen);;
    ~StoreRule();

    float CalculateScore();
    bool FindPlot();
    void EnterPlot(Plot* plot);
    void LeavePlot(Plot* plot);
    void Update();
    bool IsSatisfied() override;
private:
	const int maxDistance = 100;
	float materialNeed;
};

