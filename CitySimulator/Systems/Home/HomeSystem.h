#pragma once
#include "../Base/BaseSystem.h"

/**
* \brief Home systems that tracks and handles collective home plots and events
*/

class HomeSystem :
	public BaseSystem
{
public:
	HomeSystem();
	~HomeSystem();
	int Register(Plot* plot) override;
	void Update() override;
	float GetSatisfaction() const override;
	void EndDay() override;
	int GetTotalFamily()const;
	std::string ContentString()override;
private:
	const int maxOccupantCount = 20;
	const int scorePerOccupant = 10;
	const int overPenalty = 5;

};

