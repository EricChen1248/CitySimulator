#include "../Controllers/CoreController.h"
#include "Road.h"



Road::Road(Plot* plotOne, Plot* plotTwo) : plotOne(plotOne), plotTwo(plotTwo), level(1), capacity(100), citizenCount(0), lifespan(50.f), isBroken(false)
// TODO: number of capacity, lifespan 
{
    shape = Line(plotOne->Coords(), plotTwo->Coords(), LIGHT_GREY, 1.3);
}


Road::~Road()
{
}

float Road::Speed()
{
	// Traffic jam
	// TODO: 0.2 or ?
	if (isBroken)
		return 0.01; // can pass but very slowly
	
	return static_cast<float>(level) - 0.2f * (citizenCount > capacity);
}


int Road::LevelUp()
{
	// TODO: number
	level++;
	capacity += 20; 
	lifespan = 50; // replenish
	shape.ChangeThickness(1); // TODO :thickness
	return 30; // cost 
}


int Road::Repair()
{	
	// TODO: number
	isBroken = false;
	lifespan = 50; // replenish
	shape.ChangeColor(LIGHT_GREY);
	return 30; // repair cost 

}

int Road::PerformClick()
{
	if (isBroken)
		return Repair();

	return LevelUp();
}

void Road::Enter()
{
	citizenCount++;
}

void Road::Leave()
{
	citizenCount--;
	lifespan -= 0.01; //TODO:0.01
}


bool Road::IsRoad(Plot* plotOne, Plot* plotTwo) const
{
	if (this->plotOne == plotOne && this->plotTwo == plotTwo)
		return true;
	if (this->plotOne == plotTwo && this->plotTwo == plotOne)
		return true;
	return false;
}


void Road::EndDay()
{
	// If road's level is higher than one, it should depreciate.
	if (level > 1)
		lifespan -= 1; //TODO: 1

	// Check if the road is broken
	if (lifespan < 0)
		isBroken = true;
		shape.ChangeColor(RED);
}

void Road::Render() const
{
	shape.Render(CoreController::SfmlController()->Window());
}
