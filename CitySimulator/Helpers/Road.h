#pragma once
#include <SFML/Graphics.hpp>

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

	sf::ConvexShape shape;

public:
	Road(Plot* plotOne, Plot* plotTwo);
	~Road();

	//Getter
	float Speed();

	//Setter
	int LevelUp();
	int Repair();


	//Function
	void Enter();
	void Leave();
	bool isRoad(Plot* plotOne, Plot* plotTwo);
	void EndDay();
	void Render();

};

