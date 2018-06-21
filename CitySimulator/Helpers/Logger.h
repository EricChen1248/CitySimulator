#pragma once
#include <string>

/**
 * \brief Singleton logger that logs event in a log file
 */
class Logger
{
public:
    Logger();
    ~Logger();
    /**
     * \brief Writes a string message to log file
     * \param log message to write
     */
    static void Log(const std::string& log);
private:
    static Logger* instance;
};

