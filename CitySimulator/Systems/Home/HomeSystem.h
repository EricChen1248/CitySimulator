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
	void Register(Plot* plot) override;
	void Update() override;
	void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
	void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
	void EndDay() override;
private:
	const int maxOccupantCount = 20;
	const int scorePerOccupant = 10;
	const int overPenalty = 5;

};

