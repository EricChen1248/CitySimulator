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
	void Register(Plot* plot) override;
	void Update() override;
	void LogSatisfied(Citizen* citizen, BaseRule* rule) override;
	void LogUnsatisfied(Citizen* citizen, BaseRule* rule) override;
	void EndDay() override;
private:
	const int maxOccupantCount = 100;
	const int scorePerOccupant = 20;
	const int overPenalty = 15;
};

