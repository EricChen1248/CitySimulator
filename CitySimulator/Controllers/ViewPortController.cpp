#include "./ViewPortController.h"
#include "CoreController.h"

ViewPortController::ViewPortController()
{
    viewX = 512;
    viewY = 384;
    scrollSize = 1;
    modifier = 1;
    view.setSize(viewX * 2, viewY * 2);
    UpdateView();
}

ViewPortController::~ViewPortController() = default;

/**
 * \brief Converts game screen coordinates to viewport coordinates
 * \param sCoords Screen coordinates to convert to viewport coordinates
 * \return Converted viewport coordinates
 */
ScreenCoordinate ViewPortController::ToDrawCoord(ScreenCoordinate sCoords) const
{
    sCoords.X = sCoords.X * scrollSize;
    sCoords.Y = sCoords.Y * scrollSize;
    return sCoords;
}

/**
 * \brief Handles zoom when scrolling
 * \param event Scroll event that holds the event data
 */
void ViewPortController::HandleScroll(sf::Event& event)
{
    const auto oldScroll = scrollSize;
    scrollSize += event.mouseWheelScroll.delta > 0 ? 0.04f : -0.04f;
    modifier = scrollSize / oldScroll;
}

/**
 * \brief Resets the modifier to 1 after scrolling
 */
void ViewPortController::ResetMod()
{
    modifier = 1;
}

/**
 * \brief Moves the view to the left
 */
void ViewPortController::Left()
{
    viewX += 10;
    UpdateView();
}

/**
 * \brief Moves the view to the right
 */
void ViewPortController::Right()
{
    viewX -= 10;
    UpdateView();
}

/**
 * \brief Moves the view up
 */
void ViewPortController::Up()
{
    viewY += 10;
    UpdateView();
}

/**
 * \brief Moves the view down
 */
void ViewPortController::Down()
{
    viewY -= 10;
    UpdateView();
}

void ViewPortController::UpdateView()
{
    view.setCenter(static_cast<float>(viewX), static_cast<float>(viewY));
    CoreController::Instance()->SfmlController()->Window()->setView(view);
}
