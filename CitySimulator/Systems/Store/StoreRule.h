#pragma once
#include "c:\Users\David Li\Documents\GitHub\CitySimulator\CitySimulator\Systems\Base\BaseRule.h"

/**
* \brief Store rule that handles the consumption needs of our citizens
*/
class StoreRule :	public BaseRule
{
public:
	StoreRule();
	~StoreRule();
private:
	 StoreRule(Citizen& citizen);;
    ~StoreRule();

    float CalculateScore();
    bool FindPlot();
    void EnterPlot(Plot* plot);
    void LeavePlot(Plot* plot);
    void Update();
    bool IsSatisfied() override;

};

