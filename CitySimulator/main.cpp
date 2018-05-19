#include "Controllers/CoreController.h"
#include "Helpers/Logger.h"

int main(int argc, char* argv[])
{
    auto *core = new CoreController();
    auto *logger = new Logger();
    Logger::Instance()->Log("test");
    core->Start();
   
    delete logger;    
    delete core;
    return 0;
}

