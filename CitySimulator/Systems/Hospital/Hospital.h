#pragma once
#include "../Base/Base.h"

class HospitalRule;

/**
 * \brief Hospital Class that handles the Hospital plots of our city
 */
class Hospital : public Base
{
friend HospitalRule;
friend HospitalSystem;

    public:
    Hospital(Plot* plot);
    ~Hospital() = default;
    void EndDay() override;
    void Enter();
	void NewMember(Citizen* citizen);
	int Destroy() override;
	bool isFull() { return members.Count() >= capacity;};
	std::string ContentString();

private:
    int cost;
    int capacity; 
    int citizenCount; 
	List<Citizen*> members;
};

