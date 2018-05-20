#pragma once
#include <string>

/**
 * \brief Singleton logger that logs event in a log file
 */
class Logger
{
public:
    static Logger* Instance() { return instance;};
    
    Logger();
    ~Logger();
    /**
     * \brief Writes a string message to log file
     * \param log message to write
     */
    void Log(std::string log) const;
    
private:
    static Logger* instance;
    const std::string logfile = "./Log.log";
};

