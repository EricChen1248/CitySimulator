#pragma once
#include "../Base/BaseSystem.h"

/**
* \brief Food systems that tracks and handles collective food plots and events
*/
class BankSystem : public BaseSystem
{
public:
	BankSystem();
	~BankSystem();
	int Register(Plot* plot) override;
    int Cost() const override { return 6000; };
	void Update() override;
	void NewDay() override;
	void NewClientWait(const float& time);
	std::string ContentString() override;
	float GetSatisfaction() const override;
	
private:
	const int maxOccupantCount = 20;
	const int scorePerOccupant = 10;
	const int overPenalty = 5;
	List<float> waitTimeList{};
	float averageCustomerPerBank;
};

