#include "./MapController.h"
#include "SFMLController.h"

MapController::MapController()
{
    xOffset = 512;
    yOffset = 384;
}


MapController::~MapController()
{
}

ScreenCoordinate MapController::toDrawCoord(ScreenCoordinate& sCoords) const
{
    sCoords.X += xOffset;
    sCoords.Y += yOffset;
    return sCoords;
}
