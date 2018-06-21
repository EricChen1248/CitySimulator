#include "Coordinate.h"
#include <cmath>
#include "Constants.h"

const int X_CHANGE[6] = { 0, 0, 1, 1,-1,-1};
const int Y_CHANGE[6] = { 1,-1,-1, 0, 1, 0};
const int Z_CHANGE[6] = {-1, 1, 0,-1, 0, 1};

Coordinate::Coordinate(const float x, const float y, const float z): x(x) , y(y), z(z)
{
}

Coordinate::~Coordinate() = default;

/**
 * \brief Converts game hexagonal coordinates to SFML cube coordinates
 * \return Returns the converted coordinates
 */
ScreenCoordinate Coordinate::ToScreenCoordinates() const
{
    const float sX = x * SIN60 - y * SIN60;
    const float sY = x * COS60 + y * COS60 - z;
    return {sX * 60, sY * 60};
}

/**
 * \brief Generates a possible list of neighbours of the coordinate
 * \return Dynamic array of coordinates that hold the neighbours
 */
Coordinate* Coordinate::GetNeighbours() const
{
    Coordinate* list = new Coordinate[6];
    for (int i = 0; i < 6; ++i)
    {
        const Coordinate coords(static_cast<int>(x) + X_CHANGE[i], static_cast<int>(y) + Y_CHANGE[i], static_cast<int>(z) + Z_CHANGE[i]);
        list[i] = coords;        
    }
    return list;
}

/**
 * \brief Splices a coordinate that is between the source and target based on prev update time;
 * \param dest Destination coordinate to move towards
 * \param deltaTime Time since prev update
 * \return Spliced coordinate between source and destination
 */
Coordinate Coordinate::MoveTowards(const Coordinate dest, float deltaTime) const
{
    const float smoothness = 8;
    deltaTime *= 3 / smoothness;
    float X = x + (dest.x > x + deltaTime ? 1 : dest.x < x - deltaTime ? -1 : 0) * deltaTime;
    float Y = y + (dest.y > y + deltaTime ? 1 : dest.y < y - deltaTime ? -1 : 0) * deltaTime;
    float Z = z + (dest.z > z + deltaTime ? 1 : dest.z < z - deltaTime ? -1 : 0) * deltaTime;
    for (int i = 0; i < smoothness - 1; ++i)
    {
        X += (dest.x > X + deltaTime ? 1 : dest.x < X - deltaTime ? -1 : 0) * deltaTime;
        Y += (dest.y > Y + deltaTime ? 1 : dest.y < Y - deltaTime ? -1 : 0) * deltaTime;
        Z += (dest.z > Z + deltaTime ? 1 : dest.z < Z - deltaTime ? -1 : 0) * deltaTime;
    }
    return {X, Y, Z};
}

/**
 * \brief Returns if a coordinate is within 0.01f of another
 * \param other Other coordinate to compare to
 * \return True if coordinate distance is within 0.01f
 */
bool Coordinate::operator==(const Coordinate& other) const
{
    return abs(x - other.x) + abs(y - other.y) + abs(z - other.z) < 0.1f;
}

bool Coordinate::operator!=(const Coordinate& other) const
{
    return !(*this == other);
}

/**
 * \brief Calculates and returns the manhattan distance between two coordinates
 * \param coords Other coordinate to compare to
 * \return Integer of the manhattan distance
 */
int Coordinate::Distance(Coordinate& coords) const
{
    return static_cast<int>(abs(x - coords.x) + abs(y - coords.y) + abs(z - coords.z)) / 2;
}
