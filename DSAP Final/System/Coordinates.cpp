#include "Coordinates.h"
#include "../System/Constants.h"
#include <cmath>


Coordinates::Coordinates(const int x = 0, const int y = 0, const int z = 0): x(x) , y(y), z(z)
{
}

Coordinates::~Coordinates() = default;

ScreenCoordinates Coordinates::ToScreenCoordinates() const
{
    float x = x * COS60 - y * COS60;
    float y = x * SIN60 + y * SIN60 - z;
    return {x, y};
}

int Coordinates::Distance(Coordinates& coords) const
{
    return (abs(x-  coords.x) + abs(y-  coords.y) + abs(z - coords.z)) / 2;
}
