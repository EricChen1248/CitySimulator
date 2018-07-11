#include "Road.h"

#include "Constants.h"
#include "../Systems/Plot/Plot.h"
#include "../Controllers/SFMLController.h"
#include "../Controllers/CoreController.h"


Road::Road(Plot* plotOne, Plot* plotTwo) : plotOne(plotOne), plotTwo(plotTwo), level(1), capacity(10), citizenCount(0),
                                           lifespan(baseLifeSpan), isBroken(false), isRiver(false)
{
    shape = Line(plotOne->Coords(), plotTwo->Coords(), BASE_ROAD_COLOR, 1.8f);
}


Road::~Road()
= default;

float Road::Speed() const
{
    if (isRiver) return 0.f;
	if (isBroken)
		return 0.01f; // can pass but very slowly
	
	// Traffic jam
	return 1 + static_cast<float>(level - 1) * 0.2f - 0.2f * (citizenCount > capacity ? 1.f : 0.f);
}

bool Road::IsRiver() const
{
	return isRiver;
}


int Road::LevelUp()
{
    if (isRiver)
    {
        if (plotOne->IsRiver()) plotOne->BuiltBridge();
        if (plotTwo->IsRiver()) plotTwo->BuiltBridge();
        isRiver = false;
        shape.SetColor(BASE_ROAD_COLOR);
    }
	level++;
	capacity += 2; 
	lifespan = baseLifeSpan; // replenish
	shape.ChangeThickness(1 + level * 0.8f);
	return upgradeCosts[level-1]; // cost 
}


int Road::Repair()
{	
	isBroken = false;
	lifespan = baseLifeSpan; // replenish
	shape.ChangeColor(BASE_ROAD_COLOR);
	return upgradeCosts[level - 1] / 5;

}

int Road::Cost() const
{
    return isBroken ? upgradeCosts[level - 1] / 5: upgradeCosts[level];
}

void Road::MarkAsRiver()
{
    shape.SetColor(TRANSPARENT);
	isRiver = true;
	level = 0;
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
	lifespan -= 0.1f;
}


bool Road::IsRoad(const Plot* plotOne, const Plot* plotTwo) const
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
		lifespan -= 1;

	// Check if the road is broken
	if (lifespan < 0)
	{
		isBroken = true;
		shape.ChangeColor(RED);
	}
}

void Road::Render() const
{
	shape.Render(CoreController::SfmlController()->Window());
}

std::string Road::ContentString() const
{
    std::stringstream ss;
    if (isBroken)
    {
        ss << "Road is broken\nrepair it to use.";
    }
    else if (isRiver)
    {
        ss << "This is under the\nriver. Build a bridge\nto cross.";
    }
    else
    {
        ss << "Upgrade the road\nto increase capacity\nand speed";
    }
    
    ss << std::endl << std::endl << "Current Level: " << level << std::endl << "Current Speed: " << Speed();
    
    return ss.str();
}

std::string Road::ButtonString() const
{
    if (isBroken)
    {
        return "Repair";
    }
    if (isRiver)
    {
        return "Build bridge";
    }
    return "Upgrade";
}

