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
    void PruneDead();
	void EndDay();
	void CalculateSatisfaction() const;
    const LinkedList<Citizen*>& Citizens() const { return citizens; }
private:
    LinkedList<Citizen*> citizens;
    int citizenCount;
};

