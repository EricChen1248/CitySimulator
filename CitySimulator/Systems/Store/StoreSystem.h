#pragma once
#include "..\Base\BaseSystem.h"

/**
* \brief Store systems that tracks and handles collective store plots and events
*/
class StoreSystem :	public BaseSystem
{
public:
	StoreSystem();
	~StoreSystem();
	int Register(Plot* plot) override;
	void Update() override;
	void EndDay() override;
    float GetSatisfaction() const override;
    inline void NewDay() override;
    int Cost() const override { return 5000; };
    std::string ContentString() override;
private:
	const int maxOccupantCount = 100;
	const int scorePerOccupant = 20;
	const int overPenalty = 15;
};

