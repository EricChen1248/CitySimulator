#pragma once
#include "../Base/BaseSystem.h"

/**
 * \brief School systems that tracks and handles collective food plots and events
 */
class SchoolSystem : public BaseSystem
{
	
public:
    SchoolSystem();
    ~SchoolSystem();

    int Register(Plot* plot) override;
    void Update() override;
	float GetSatisfaction() const override;
    void EndDay() override;
	void Toggle() override;
	int Cost() const override;
	std::string ContentString() override;
private :
    //const int scorePerOccupant = 10;
    //const int overPenalty = 5;

	bool isPremium;
};

