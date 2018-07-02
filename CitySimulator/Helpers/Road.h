#pragma once
#include <SFML/Graphics.hpp>
#include "Line.h"

class Plot;
class Road
{
private:
	Plot* plotOne;
	Plot* plotTwo;
	int level;
	int capacity;
	int citizenCount;
	float lifespan{};
	bool isBroken;

	Line shape;

public:
	Road(Plot* plotOne, Plot* plotTwo);
	~Road();

	//Getter
	float Speed();

	//Setter
	int LevelUp();
	int Repair();


	//Function
	int PerformClick();
	void Enter();
	void Leave();
	bool IsRoad(Plot* plotOne, Plot* plotTwo) const;
	void EndDay();
	void Render() const;

};

