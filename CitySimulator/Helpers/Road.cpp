#include "../Controllers/CoreController.h"
#include "Road.h"



Road::Road(Plot* plotOne, Plot* plotTwo) : plotOne(plotOne), plotTwo(plotTwo), level(1), capacity(100), citizenCount(0), lifespan(50.f)
// TODO: number of capacity, lifespan 
{
}


Road::~Road()
{
	delete this->plotOne;
	delete this->plotTwo;
}

float Road::Speed()
{
	// Traffic jam
	// TODO: 0.2 or ?
	return static_cast<float>(level) - 0.2f * (citizenCount > capacity);
}


int Road::LevelUp()
{
	// TODO: number
	level++;
	capacity += 20; 
	lifespan = 50; // replenish

	return 30; // cost 
}


void Road::Enter()
{
	citizenCount++;
	//lifespan

}

void Road::Leave()
{

}


bool Road::isRoad(Plot* plotOne, Plot* plotTwo)
{
	if (this->plotOne == plotOne && this->plotTwo == plotTwo)
		return true;
	if (this->plotOne == plotTwo && this->plotTwo == plotOne)
		return true;
	return false;
}


void Road::EndDay()
{
	//TODO:Level2 ¥H¤W´î·l
	//TODO:°»´ú´î·l
}

void Road::Render()
{
	//CoreController::Instance()->GetUIController()->RenderLine(shape);
}