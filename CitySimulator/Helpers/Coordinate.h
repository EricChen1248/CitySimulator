#pragma once
#include "../Collections/List.h"

/**
 * \brief Helper struct to interface between our hexagonal grid coordinates to SFML square coordinates
 */
struct ScreenCoordinate
{
    ScreenCoordinate(const float x, const float y) : X(x), Y(y) {};
    float X;
    float Y;
};


/**
 * \brief Hexagonal Coordinate System for the game
 */
class Coordinate
{
public:
    Coordinate(float x, float y, float z);
    ~Coordinate();
    int Distance(Coordinate &coords) const;
    ScreenCoordinate ToScreenCoordinates() const;
    Coordinate* GetNeighbours() const;
    Coordinate MoveTowards(Coordinate other, float deltaTime) const;
    bool operator==(const Coordinate& other) const;
private:
    float x;
    float y;
    float z;
};

