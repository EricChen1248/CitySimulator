#include "./ViewPortController.h"
#include "CoreController.h"
#include <iostream>
#include "../Helpers/HeaderFunctions.h"

ViewPortController::ViewPortController()
{
    viewX = 512;
    viewY = 384;
    scrollSize = 1;
    modifier = 1;
    gameView.setSize(static_cast<float>(viewX * 2), static_cast<float>(viewY * 2));
    uiView.setCenter(static_cast<float>(WINDOW_WIDTH) / 2, static_cast<float>(WINDOW_HEIGHT) / 2);
    uiView.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
    UpdateGameView();
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
    scrollSize = Clamp(scrollSize + (event.mouseWheelScroll.delta > 0 ? 0.04f : -0.04f), 0.35f, 1.25f);
    modifier = scrollSize / oldScroll;
    std::cout << scrollSize;
}

/**
 * \brief Resets the modifier to 1 after scrolling
 */
void ViewPortController::ResetMod()
{
    modifier = 1;
}

/**
 * \brief Moves the gameView to the left
 */
void ViewPortController::Left()
{
    viewX += 10;
}

/**
 * \brief Moves the gameView to the right
 */
void ViewPortController::Right()
{
    viewX -= 10;
}

/**
 * \brief Moves the gameView up
 */
void ViewPortController::Up()
{
    viewY += 10;
}

/**
 * \brief Moves the gameView down
 */
void ViewPortController::Down()
{
    viewY -= 10;
}

/**
 * \brief Update game view center and sets renderer to use game view
 */
void ViewPortController::UpdateGameView()
{
    gameView.setCenter(static_cast<float>(viewX), static_cast<float>(viewY));
    CoreController::Instance()->SfmlController()->Window()->setView(gameView);
}

/**
 * \brief Set renderer to use uiView
 */
void ViewPortController::UpdateUIView() const
{
    CoreController::Instance()->SfmlController()->Window()->setView(uiView);
}
