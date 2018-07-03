#pragma once
#include "Citizen.h"
#include "../../Collections/List.h"
#include "../../Collections/LinkedList.h"


class CitizenSystem
{
public:
    CitizenSystem();
    ~CitizenSystem();
    void Update() const;
    void Render() const;
    void PruneDead();
	//TODO: new Day
	void NewDay();
	void EndDay();
	void CalculateSatisfaction() const;
    const LinkedList<Citizen*>& Citizens() const { return citizens; }
	
private:
	void NewCitizen();
	void PeopleMarry();
    LinkedList<Citizen*> citizens;
    int citizenCount;
};

