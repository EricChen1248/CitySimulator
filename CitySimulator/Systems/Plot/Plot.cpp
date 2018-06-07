#include "Plot.h"
#include "../../Controllers/CoreController.h"
#include "../../Helpers/Constants.h"


Plot::Plot(const int x, const int y, const int z) : coords(x, y, z), size(10.f), shape(sf::CircleShape(size)),
                                                    currentType(nullptr)
{
    shape.setFillColor(EMPTY_PLOT_COLOR);
    sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
}

sf::CircleShape& Plot::GetShape()
{
    const auto tCoords = CoreController::Instance()->GetViewportController()->ToDrawCoord(sCoords);
    shape.setPosition(tCoords.X, tCoords.Y);
    return shape;
}

bool Plot::InBounds() const
{
    const sf::Window* window = CoreController::Instance()->SfmlController()->Window();
    const auto &mousePos = sf::Mouse::getPosition(*window);
    return shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
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

void Plot::EndDay()
{
    if (currentType != nullptr)
    {
        currentType->EndDay();
    }
}

/**
 * \brief Selects the plot as clicked
 */
void Plot::Click()
{
    
}

Plot::~Plot()
{
    delete currentType;
}
