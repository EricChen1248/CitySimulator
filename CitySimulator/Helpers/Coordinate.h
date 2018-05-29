#pragma once

/**
 * \brief Helper struct to interface between our hexagonal grid coordinates to SFML square coordinates
 */


struct ScreenCoordinate
{
    ScreenCoordinate(const float x = 0, const float y = 0) : X(x), Y(y) {};
    float X;
    float Y;
};


/**
 * \brief Hexagonal Coordinate System for the game
 */
class Coordinate
{
public:
    Coordinate(int x, int y, int z) : Coordinate(static_cast<float>(x),static_cast<float>(y),static_cast<float>(z)) {};
    Coordinate(float x = 0, float y = 0, float z = 0);
    ~Coordinate();
    
    int X() const { return static_cast<int>(x); }
    int Y() const { return static_cast<int>(y); }
    int Z() const { return static_cast<int>(z); }
    
    int Distance(Coordinate &coords) const;
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

