#pragma once
#include "../Base/Base.h"

class HospitalRule;

/**
 * \brief Hospital Class that handles the Hospital plots of our city
 */
class Hospital : public Base
{
friend HospitalRule;

    public:
    Hospital(Plot* plot);
    ~Hospital() = default;
    void EndDay() override;
    void Enter();
	void NewMember(Citizen* citizen);
	int Destroy() override;
	std::string ContentString();

private:
    int cost;
    int capacity; 
    int citizenCount; 
	List<Citizen*> members;
};

