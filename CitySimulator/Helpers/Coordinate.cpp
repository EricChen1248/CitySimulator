#include "Coordinate.h"
#include <cmath>
#include "Constants.h"

const int xChange[6] = { 0, 0, 1, 1,-1,-1};
const int yChange[6] = { 1,-1,-1, 0, 1, 0};
const int zChange[6] = {-1, 1, 0,-1, 0, 1};

Coordinate::Coordinate(const float x = 0, const float y = 0, const float z = 0): x(x) , y(y), z(z)
{
}

Coordinate::~Coordinate() = default;

ScreenCoordinate Coordinate::ToScreenCoordinates() const
{
    const float sX = x * SIN60 - y * SIN60;
    const float sY = x * COS60 + y * COS60 - z;
    return {sX * 60, sY * 60};
}

Coordinate* Coordinate::GetNeighbours() const
{
    Coordinate* list = new Coordinate[6];
    for (int i = 0; i < 6; ++i)
    {
        const Coordinate coords(x + xChange[i], y + yChange[i], z + zChange[i]);
        list[i] = coords;        
    }
    return list;
}

Coordinate Coordinate::MoveTowards(const Coordinate other, const float deltaTime) const
{
    const float X = x + (other.x > x ? 1 : other.x < x ? -1 : 0) * deltaTime;
    const float Y = y + (other.y > y ? 1 : other.y < y ? -1 : 0) * deltaTime;
    const float Z = z + (other.z > z ? 1 : other.z < z ? -1 : 0) * deltaTime;
    return {X, Y, Z};
}

bool Coordinate::operator==(const Coordinate& other) const
{
    return abs(x - other.x) + abs(y - other.y) + abs(z - other.z) < 0.01f;
}

int Coordinate::Distance(Coordinate& coords) const
{
    return (abs(x-  coords.x) + abs(y-  coords.y) + abs(z - coords.z)) / 2;
}
