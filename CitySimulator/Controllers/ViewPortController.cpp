#include "./ViewPortController.h"

ViewPortController::ViewPortController()
{
    xOffset = 512;
    yOffset = 384;
}

ViewPortController::~ViewPortController() = default;

/**
 * \brief Converts game screen coordinates to viewport coordinates
 * \param sCoords Screen coordinates to convert to viewport coordinates
 * \return Converted viewport coordinates
 */
ScreenCoordinate ViewPortController::ToDrawCoord(ScreenCoordinate& sCoords) const
{
    sCoords.X += xOffset;
    sCoords.Y += yOffset;
    return sCoords;
}
