#pragma once
#include "../Helpers/Coordinate.h"

/**
 * \brief Handles the viewport of the screen
 */
class ViewPortController
{
public:
    ViewPortController();
    ~ViewPortController();
    ScreenCoordinate ToDrawCoord(ScreenCoordinate& sCoords) const;
    
private:
    int xOffset;
    int yOffset;
};

