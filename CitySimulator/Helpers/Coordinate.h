#pragma once

struct ScreenCoordinates
{
    ScreenCoordinates(const float x, const float y) : X(x), Y(y) {};
    float X;
    float Y;
};

class Coordinates
{
public:
    Coordinates(int x, int y, int z);
    ~Coordinates();
    int Distance(Coordinates &coords) const;
    ScreenCoordinates ToScreenCoordinates() const;
private:
    int x;
    int y;
    int z;
};

