#include "ViewPortController.h"
#include "CoreController.h"
#include "UIController.h"
#include "../Helpers/Constants.h"
#include "../Helpers/HelperFunctions.h"

ViewPortController::ViewPortController()
{
    scrollSize = 1;
    gameView.setSize(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT));
    gameView.setCenter(Coordinate(0,0,0).ToScreenCoordinates().ToVector2F());
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
    // Clamp to maximum / minimum scrolling and recalculate new deltaChange
    const float newScroll = Clamp(scrollSize * deltaChange, 0.7f, 4.f * RIGHT / 16);
    deltaChange = newScroll / scrollSize;
    
    scrollSize = newScroll;
    
    gameView.zoom(deltaChange);
}


/**
 * \brief Moves the gameView to the left
 */
void ViewPortController::Left(const float i)
{
    gameView.move(10 * scrollSize * i, 0);
}

/**
 * \brief Moves the gameView to the right
 */
void ViewPortController::Right(const float i)
{
    gameView.move(-10 * scrollSize * i, 0);
}

/**
 * \brief Moves the gameView up
 */
void ViewPortController::Up(const float i)
{
    gameView.move(0, 10 * scrollSize * i);
}

/**
 * \brief Moves the gameView down
 */
void ViewPortController::Down(const float i)
{
    gameView.move(0, -10 * scrollSize * i);
}


/**
 * \brief Update game view center and sets renderer to use game view
 */
void ViewPortController::UpdateGameView() const
{
    CoreController::SfmlController()->Window()->setView(gameView);
}

/**
 * \brief Set renderer to use uiView
 */
void ViewPortController::UpdateUIView() const
{
    CoreController::SfmlController()->Window()->setView(uiView);
}
