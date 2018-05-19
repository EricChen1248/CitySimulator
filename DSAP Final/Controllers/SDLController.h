#pragma once
#include "SDL.h"

class SDLController
{
friend class CoreController;
    // Constructors and Destructors
    SDLController();
    ~SDLController();
    
    // Properties
    bool IsRunning() const;
    
    // Methods
    void InitSDL();
    void Render() const;
    
    // Backing variables
    bool isRunning;
    SDL_Window *window{};
    SDL_Renderer *renderer{};
};

