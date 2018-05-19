#include "SDLController.h"
#include <iostream>
#include "CoreController.h"


/**
 * \brief Initializes window and renderer for sdl
 */
SDLController::SDLController()
{
    window = nullptr;
    renderer = nullptr;
    
    InitSDL();
}


SDLController::~SDLController()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "SDL quit" << std::endl;
}

bool SDLController::IsRunning() const
{
    return isRunning;
}

/**
 * \brief 
 */
void SDLController::Render() const
{
    SDL_RenderClear(renderer);
    
    // this is where we would add stuff to render
    
    SDL_RenderPresent(renderer);
}

/**
 * \brief Initializes the SDL
 */
void SDLController::InitSDL() 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized" << std::endl;
        window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED - 50, 1280, 720, SDL_WINDOW_SHOWN);
        if(window)
        {
            std::cout << "Window created" << std::endl;
        }
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
            std::cout << "Renderer Created" << std::endl;
        }

        
    
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
}