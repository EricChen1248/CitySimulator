#include "./ViewPortController.h"
#include "CoreController.h"
#include "../Helpers/HelperFunctions.h"

ViewPortController::ViewPortController()
{
    scrollSize = 1;
    gameView.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
    uiView.setCenter(static_cast<float>(WINDOW_WIDTH) / 2, static_cast<float>(WINDOW_HEIGHT) / 2);
    uiView.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
    UpdateGameView();
}

ViewPortController::~ViewPortController() = default;

/**
 * \brief Handles zoom when scrolling
 * \param event Scroll event that holds the event data
 */
void ViewPortController::HandleScroll(sf::Event& event)
{
    float deltaChange = -event.mouseWheelScroll.delta / 10 + 1.f;
    // Clamp to maximum / minimum scrolling and recalculate new delta change
    const float newScroll = Clamp(scrollSize * deltaChange, 0.7f, 4.f);
    deltaChange = newScroll / scrollSize;
    
    scrollSize = newScroll;
    
    gameView.zoom(deltaChange);
}


/**
 * \brief Moves the gameView to the left
 */
void ViewPortController::Left()
{
    gameView.move(10 * scrollSize, 0);
}

/**
 * \brief Moves the gameView to the right
 */
void ViewPortController::Right()
{
    gameView.move(-10 * scrollSize, 0);
}

/**
 * \brief Moves the gameView up
 */
void ViewPortController::Up()
{
    gameView.move(0, 10 * scrollSize);
}

/**
 * \brief Moves the gameView down
 */
void ViewPortController::Down()
{
    gameView.move(0, -10 * scrollSize);
}

/**
 * \brief Update game view center and sets renderer to use game view
 */
void ViewPortController::UpdateGameView() const
{
    //gameView.setCenter(static_cast<float>(viewX), static_cast<float>(viewY));
    CoreController::SfmlController()->Window()->setView(gameView);
}

/**
 * \brief Set renderer to use uiView
 */
void ViewPortController::UpdateUIView() const
{
    CoreController::SfmlController()->Window()->setView(uiView);
}
