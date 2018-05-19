#include "Coordinates.h"
#include <cmath>
#include "Constants.h"


Coordinates::Coordinates(const int x = 0, const int y = 0, const int z = 0): x(x) , y(y), z(z)
{
}

Coordinates::~Coordinates() = default;

ScreenCoordinates Coordinates::ToScreenCoordinates() const
{
    const float sX = x * COS60 - y * COS60;
    const float sY = x * SIN60 + y * SIN60 - z;
    return {sX, sY};
}

int Coordinates::Distance(Coordinates& coords) const
{
    return (abs(x-  coords.x) + abs(y-  coords.y) + abs(z - coords.z)) / 2;
}
