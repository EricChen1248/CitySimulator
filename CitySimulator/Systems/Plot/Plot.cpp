#include "Plot.h"
#include "../../Controllers/CoreController.h"


Plot::Plot(const int x, const int y, const int z) : coords(x, y, z), size(10.f), shape(CircleShape(size)),
                                                    currentType(nullptr)
{
    shape.setFillColor(Color(200, 200, 200));
    sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
}

CircleShape& Plot::GetShape()
{
    const auto tCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    shape.setPosition(tCoords.X, tCoords.Y);
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


Plot::~Plot() = default;
