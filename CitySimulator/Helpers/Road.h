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
	bool isRiver;
	Line shape;

public:
	Road(Plot* plotOne, Plot* plotTwo);
	~Road();
    static const int MAX_SPEED = 10;
	//Getter
	float Speed() const;
	bool IsRiver() const;


	//Setter
	int LevelUp();
	int Repair();
	void MarkAsRiver();

	//Function
	int PerformClick();
	void Enter();
	void Leave();
	bool IsRoad(Plot* plotOne, Plot* plotTwo) const;
	void EndDay();
	void Render() const;

};

