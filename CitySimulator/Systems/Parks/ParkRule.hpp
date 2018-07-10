#pragma once
#include "../Base/BaseRule.h"
#include "../../Helpers/Coordinate.h"

class Plot;
class ParkRule : public BaseRule
{
public:
    ParkRule(Citizen& citizen);
    ~ParkRule();
    float CalculateScore() override;
    bool FindPlot() override;
    void EnterPlot(Plot* plot) override;
    void LeavePlot(Plot* plot) override;
    void Update() override;
private:
    Plot* currentPark = nullptr;
    Coordinate parkSide;
};

