#include "Logger.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <chrono>
// =============== Singleton Interface ================
Logger* Logger::instance;

// ============ Constructors & Destructors ============
Logger::Logger()
{
    if (instance != nullptr)
    {
        Log("Instance of logger already exists. This should not happen");
        return;
    }
    std::ofstream outputStream("Log.log");
    outputStream.close();
    instance = this;
}

Logger::~Logger()
= default;

void Logger::Log(const std::string& log)
{
    time_t rawtime;
    tm timeinfo{};
    char buffer[80];

    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", &timeinfo);
    const std::string str(buffer);
    std::ofstream outputStream("Log.log", std::ios::app);
    outputStream << str << ": " << log << std::endl;
    outputStream.close();
}