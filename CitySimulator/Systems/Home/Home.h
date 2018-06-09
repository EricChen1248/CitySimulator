#pragma once
#include "../Base/Base.h"
#include "../../Collections/List.h"
#include "../Citizen/Citizen.h"
#include "../Plot/Plot.h"
class HomeRule;

class Home :	public Base
{
	friend HomeRule;
public:
	Home(Plot* plot);
	~Home() = default;
	void Register(Citizen* citizen);
	void EndDay();
	bool Full() const;
	Plot* GetPlot();
private:
	//each home has it's own capacity
	int homeCapacity;
	List<Citizen*> Residents;
	void Enter();

};
