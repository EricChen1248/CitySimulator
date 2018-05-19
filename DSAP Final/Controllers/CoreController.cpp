#include "CoreController.h"
#include <iostream>
#include <SDL.h>

CoreController *CoreController::instance;

bool CoreController::IsRunning() const
{
    return isRunning && sdlController.IsRunning();
}

CoreController::CoreController()
{
    instance = this;
    isRunning = true;
};
CoreController::~CoreController() = default;

void CoreController::Update()
{
    HandleEvents();


    
    Render();
}

void CoreController::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        default: 
            break;
    }
}

/**
 * \brief Calls on SDL controller to render the screen
 */
void CoreController::Render() const
{
    sdlController.Render();
}
