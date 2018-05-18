#include "Logger.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <iostream>

// =============== Singleton Interface ================
Logger* Logger::instance;

// ============ Constructors & Destructors ============
Logger::Logger()
{
    if (instance != nullptr)
    {
        instance->Log("Instance of logger already exists. This should not happen");
        return;
    }
    instance = this;
}

Logger::~Logger()= default;



void Logger::Log(const std::string log) const
{
    time_t rawtime;
    tm timeinfo{};
    char buffer[80];

    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", &timeinfo);
    const std::string str(buffer);
    
    std::ofstream outputStream(logfile);
    outputStream << str << ":" << log;
    outputStream.close();

}
