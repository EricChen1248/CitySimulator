#pragma once

struct ScreenCoordinate
{
    ScreenCoordinate(const float x, const float y) : X(x), Y(y) {};
    float X;
    float Y;
};

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

