#include "SDL.h"
#include "Controllers/CoreController.h"
#include "System/Logger.h"

int main(int argc, char* argv[])
{
    auto *core = new CoreController();
    auto *logger = new Logger();
    while (core->IsRunning())
    {
        core->Update();
    }
    
    Logger::Instance()->Log("test");
   
    delete logger;    
    delete core;
    return 0;
}

