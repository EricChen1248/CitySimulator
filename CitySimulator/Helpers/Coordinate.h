#pragma once

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
    Coordinate(int x, int y, int z);
    ~Coordinate();
    int Distance(Coordinate &coords) const;
    ScreenCoordinate ToScreenCoordinates() const;
private:
    int x;
    int y;
    int z;
};

