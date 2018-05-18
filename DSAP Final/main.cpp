#include "SDL.h"
#include "Controllers/CoreController.h"
#include "System/Logger.h"

int main(int argc, char* argv[])
{
    auto *core = new CoreController();
    auto *logger = new Logger();
    core->Update();
    
    Logger::Instance()->Log("test");
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    SDL_Delay(3000);

    delete logger;    
    delete core;
    return 0;
}

