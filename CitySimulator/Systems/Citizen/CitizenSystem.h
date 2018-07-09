#pragma once
#include "Citizen.h"
#include "../../Collections/LinkedList.h"

class CitizenSystem
{
public:
    CitizenSystem();
    ~CitizenSystem();
    
    void Update() const;
    void Render() const;
    
    int CitizenCount() const { return citizens.Count(); }
    void PruneDead();
    
	void NewDay();
	void EndDay();
    
    const LinkedList<Citizen*>& Citizens() const { return citizens; }
	
private:
	void NewCitizen();
	void PeopleMarry();
    LinkedList<Citizen*> citizens;
};

