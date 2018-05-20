#include "Plot.h"
#include "../../Controllers/CoreController.h"


Plot::Plot(const int x, const int y, const int z) : coords(x,y,z), size(10)
{
}

CircleShape Plot::GetShape() const
{
    sf::CircleShape circle(size);
    circle.setFillColor(Color(200,200,200));
    auto sCoords = coords.ToScreenCoordinates();
    sCoords.X -= size / 2;
    sCoords.Y -= size / 2;
    sCoords = CoreController::Instance()->GetMapController()->ToDrawCoord(sCoords);
    circle.setPosition(sCoords.X, sCoords.Y);
    return circle;
}

bool Plot::hasCoords(Coordinate coord) const
{
    return coords == coord;
}


Plot::~Plot() = default;
