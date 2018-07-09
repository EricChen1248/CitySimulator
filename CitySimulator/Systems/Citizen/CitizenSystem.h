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
    
    int CitizenCount() const { return citizens.Count() - deathCount; }
    void PruneDead();
    
	void NewDay();
	void EndDay();
    void NewDeath();
    
    void GenerateCentroids(const List<Plot*>& centers);
    
    const LinkedList<Citizen*>& Citizens() const { return citizens; }
	
private:
	void NewCitizen();
	void PeopleMarry();
    int deathCount = 0;
    LinkedList<Citizen*> citizens;
};

