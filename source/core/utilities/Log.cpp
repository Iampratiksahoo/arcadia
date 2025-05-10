#include "Log.h"

#include <cstdarg>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

void setColor(int color)
{
    std::cout << "\033[" << color << "m";
}

void resetColor()
{
    std::cout << "\033[" << 0 << "m";
}


Log* Log::m_instance = nullptr;
    
Log* Log::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new Log();
    }

    return m_instance;
}

void const Log::Print (Type logType, const char* logFormat, ...)
{
    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time;

#ifdef _WIN32
    localtime_s(&local_time, &now_time);
#else
    localtime_r(&now_time, &local_time); // Use localtime_r for POSIX systems
#endif


    va_list args;
    va_start(args, logFormat);

    // set the color of the text in the console
    setColor((int)logType);

    // print the time
    std::cout << "[" << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S") << "] ";

    // Use vprintf to print formatted output
    vprintf(logFormat, args);

    // Add a new Line
    printf("\n");

    // reset the console color
    resetColor();

    va_end(args);
}