#pragma once
#include "SFMLController.h";
#include "../Helpers/Coordinate.h"

class MapController
{
public:
    MapController();
    ~MapController();
    ScreenCoordinate toDrawCoord(ScreenCoordinate& sCoords) const;
    
private:
    
    int xOffset;
    int yOffset;
};

