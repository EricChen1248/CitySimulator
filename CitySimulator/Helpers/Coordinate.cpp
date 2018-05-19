#include "Coordinate.h"
#include <cmath>
#include "Constants.h"


Coordinate::Coordinate(const int x = 0, const int y = 0, const int z = 0): x(x) , y(y), z(z)
{
}

Coordinate::~Coordinate() = default;

ScreenCoordinate Coordinate::ToScreenCoordinates() const
{
    const float sX = x * SIN60 - y * SIN60;
    const float sY = x * COS60 + y * COS60 - z;
    return {sX * 60, sY * 60};
}

int Coordinate::Distance(Coordinate& coords) const
{
    return (abs(x-  coords.x) + abs(y-  coords.y) + abs(z - coords.z)) / 2;
}
