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
    try
    {
        core->Start();
    }
    catch(std::exception& e)
    {
        std::stringstream ss;
        ss << "Exception occured: "<< std::string(e.what()) << std::endl;
        Logger::Log(ss.str());
    }
   
    delete core;
    return 0;
}

