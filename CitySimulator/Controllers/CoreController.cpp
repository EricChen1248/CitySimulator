#include "CoreController.h"
#include "MapController.h"
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
    mapController = new MapController();
    plotSystem = new PlotSystem();
};
CoreController::~CoreController() = default;

void CoreController::Update()
{
    while(IsRunning())
    {
        HandleEvents();
        ClearRender();

        
        plotSystem->Render();
        
        PresentRender();
    
    }
}

void CoreController::HandleEvents()
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
 * \brief Renderes a texture with the SFML renderer
 */
void CoreController::Render(Drawable& shape) const
{
    sfmlController->Render(shape);
}

/**
 * \brief Update the render buffer
 */
void CoreController::PresentRender() const
{
    sfmlController->PresentRender();
}

