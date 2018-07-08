#include "Plot.h"
#include "../../Helpers/Constants.h"
#include "../../Helpers/Road.h"
#include "../../Helpers/Coordinate.h"
#include "../../Helpers/PathFinder/PathFinder.hpp"

Plot::Plot(const int x, const int y, const int z) : coords(x, y, z), shape(sf::CircleShape(size)),
                                                    currentType(nullptr), roads(6)
{
    shape.setFillColor(EMPTY_PLOT_COLOR);
    auto sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
    shape.setPosition(sCoords.X, sCoords.Y);
    for (int i = 0; i < 6; ++i)
    {
        roads.InsertLast(nullptr);
    }
}


/**
 * \brief Adds a plot type component to the plot. Update's color accordingly
 * \param base Type of plot to be registered as
 */
void Plot::Register(Base* base)
{
    if (currentType != nullptr) throw PlotBaseError("Plot is being registered but is already built");
    currentType = base;
    shape.setFillColor(base->Color());
}


/**
 * \brief Handles citizens entering plot
 * \param citizen Citizen that is entering
 */
void Plot::Enter(Citizen* citizen)
{
    ++occupantCount;
}


/**
 * \brief Handles citizens leaving the plot
 * \param citizen Citizen that is leaving
 */
void Plot::Leave(Citizen* citizen)
{
    --occupantCount;
}

void Plot::NewDay() const
{
    if (currentType != nullptr)
    {
        currentType->NewDay();
    }
}

void Plot::EndDay() const
{
    if (currentType != nullptr)
    {
        currentType->EndDay();
    }
}

void Plot::InsertNewRoad(Road* newRoad, const int i) const
{
    roads[i] = newRoad;
}

Road* Plot::GetRoad(const int i) const
{
    return roads[i];
}

Road* Plot::GetRoad(Plot* plot) const
{
    for (auto road : roads)
    {
        if (road == nullptr) continue;
        if (road->IsRoad(this, plot))
        {
            return road;
        }
    }
    return nullptr;
}

void Plot::BuiltBridge()
{
    shape.setFillColor(EMPTY_PLOT_COLOR);
    PathFinder::CheckQuadrant(this);
}

void Plot::MarkNotRiver()
{
    river = false;
}

void Plot::MarkAsRiver()
{
    shape.setFillColor(TRANSPARENT);
    river = true;
    for (auto&& road : roads)
    {
        if (road == nullptr) continue;
        road->MarkAsRiver();
    }
}

void Plot::Destroy()
{
    if (currentType == nullptr) throw PlotBaseError("Plot base is being destroyed but is empty");

    currentType->Destroy();
    delete currentType;
    currentType = nullptr;
    shape.setFillColor(EMPTY_PLOT_COLOR);
}


Plot::~Plot()
{
    roads.Dispose();
    delete currentType;
}
