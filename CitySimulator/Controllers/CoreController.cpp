#include "CoreController.h"
#include "ViewPortController.h"
#include <iostream>

CoreController *CoreController::instance;

bool CoreController::IsRunning() const
{
    return isRunning && sfmlController->IsRunning();
}

CoreController::CoreController()
{
    instance = this;
    isRunning = true;
    sfmlController = new SFMLController();
    mapController = new ViewPortController();
    plotSystem = new PlotSystem();
};
CoreController::~CoreController() = default;

void CoreController::Start() const
{
    Update();
}

/**
 * \brief Core loop of the game
 */
void CoreController::Update() const
{
    while(IsRunning())
    {
        HandleEvents();
        ClearRender();

        RenderEvents();
        
        PresentRender();
    }
}

/**
 * \brief Handles SFML events
 */
void CoreController::HandleEvents() const
{
     Event event{};
     Window* window = sfmlController->Window();
    while (window->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == Event::Closed)
            window->close();
    }

}

/**
 * \brief Calls on SFML controller to clear the screen
 */
void CoreController::ClearRender() const
{
    sfmlController->ClearRender();
}

/**
 * \brief Calls the different render events
 */
void CoreController::RenderEvents() const
{
    plotSystem->Render();
}

/**
 * \brief Update the render buffer
 */
void CoreController::PresentRender() const
{
    sfmlController->UpdateWindow();
}

