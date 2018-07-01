#include "Plot.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Road.h"

Plot::Plot(const int x, const int y, const int z) : coords(x, y, z), size(10.f), shape(sf::CircleShape(size)),
                                                    currentType(nullptr), roads(6), quadrant(0), river(false)
{
    shape.setFillColor(EMPTY_PLOT_COLOR);
    sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
}

sf::CircleShape& Plot::UpdateShape()
{
    shape.setPosition(sCoords.X, sCoords.Y);
    return shape;
}

/**
 * \brief Adds a plot type component to the plot. Update's color accordingly
 * \param base Type of plot to be registered as
 */
void Plot::Register(Base* base)
{
    delete currentType;
    currentType = base;
    shape.setFillColor(base->Color());
}


/**
 * \brief Handles citizens entering plot
 * \param citizen Citizen that is entering
 */
void Plot::Enter(Citizen* citizen)
{
    occupants.InsertLast(citizen);
}


/**
 * \brief Handles citizens leaving the plot
 * \param citizen Citizen that is leaving
 */
void Plot::Leave(Citizen* citizen)
{
    occupants.Remove(citizen);
}

void Plot::NewDay()
{
    if (currentType != nullptr)
    {
        currentType->NewDay();
    }
}

void Plot::EndDay()
{
    if (currentType != nullptr)
    {
        currentType->EndDay();
    }
    for (auto && road : roads)
    {
        break;
    }
}

void Plot::GenerateRoads()
{

}

Road* Plot::GetRoad(Plot* nextPlot)
{
	for (auto&& road : roads)
	{
		if (road->IsRoad(this, nextPlot))
			return road;
	}
	return nullptr;
}
 
void Plot::Destroy() 
{ 
    if (currentType != nullptr) 
    { 
        currentType->Destroy();
        delete currentType; 
        currentType = nullptr; 
    }    
} 
 

Plot::~Plot()
{
    delete currentType;
}
