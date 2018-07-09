#pragma once
#include "../Base/Base.h"

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
    void EndDay() override { };
    void Enter() const;
	void NewMember(Citizen* citizen);
	int Destroy() override;
	bool IsFull() const { return members.Count() >= capacity;};
	std::string ContentString() override;

private:
    int cost;
    int capacity; 
    int citizenCount; 
	List<Citizen*> members;
};

