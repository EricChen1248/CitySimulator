#include "Controllers/CoreController.h"
#include "Helpers/Logger.h"

int main(int argc, char* argv[])
{
    Logger logger;
#ifdef _DEBUG
    Logger::Log("Game Started in Debug Mode");
#else
    Logger::Log("Game Started in Release Mode");
#endif
    
    auto *core = new CoreController();
    core->Start();
   
    delete core;
    return 0;
}

