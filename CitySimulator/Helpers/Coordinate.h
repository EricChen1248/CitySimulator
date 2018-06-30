#pragma once
#include <SFML/System/Vector2.hpp>

/**
 * \brief Helper struct to interface between our hexagonal grid coordinates to SFML square coordinates
 */


struct ScreenCoordinate
{
    ScreenCoordinate(const float x = 0, const float y = 0) : X(x), Y(y) { };
    float X;
    float Y;
    sf::Vector2f ToVector2F() const { return {X, Y}; }
};


/**
 * \brief Hexagonal Coordinate System for the game
 */
class Coordinate
{
public:
    Coordinate(const int x, const int y, const int z) : Coordinate(static_cast<float>(x), static_cast<float>(y),
                                                                   static_cast<float>(z)) { };
    Coordinate(float x = 0, float y = 0, float z = 0);
    ~Coordinate();

    int X() const { return static_cast<int>(x); }
    int Y() const { return static_cast<int>(y); }
    int Z() const { return static_cast<int>(z); }

    Coordinate Left(const float offset = 1) const { return {x - offset, y + offset, z}; }
    Coordinate LeftUp(const float offset = 1) const { return {x - offset, y, z + offset}; }
    Coordinate LeftDown(const float offset = 1) const { return {x, y + offset, z - offset}; }
    Coordinate Right(const float offset = 1) const { return {x + offset, y - offset, z}; }
    Coordinate RightUp(const float offset = 1) const { return {x, y - offset, z + offset}; }
    Coordinate RightDown(const float offset = 1) const { return {x + offset, y, z - offset}; }

    int Distance(Coordinate& coords) const;
    ScreenCoordinate ToScreenCoordinates() const;
    Coordinate* GetNeighbours() const;
    Coordinate MoveTowards(Coordinate dest, float deltaTime) const;
    bool operator==(const Coordinate& other) const;
    bool operator!=(const Coordinate& other) const;
private:
    float x;
    float y;
    float z;
};

