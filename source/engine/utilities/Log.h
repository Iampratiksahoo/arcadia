#ifndef LOG_H
#define LOG_H

#define AC_LOG(logFormat, ...)			Log::GetInstance()->Print(Log::Type::LOG,       logFormat, ##__VA_ARGS__)
#define AC_NOTICE(logFormat, ...)		Log::GetInstance()->Print(Log::Type::HIGHLIGHT, logFormat, ##__VA_ARGS__)
#define AC_WARN(logFormat, ...)			Log::GetInstance()->Print(Log::Type::WARNING,   logFormat, ##__VA_ARGS__)
#define AC_SUCCESS(logFormat, ...)		Log::GetInstance()->Print(Log::Type::SUCCESS,   logFormat, ##__VA_ARGS__)
#define AC_ERROR(logFormat, ...)		Log::GetInstance()->Print(Log::Type::ERROR,     logFormat, ##__VA_ARGS__)
class Log
{
public:
    enum Type
    {
        LOG = 37,       // WHITE
        HIGHLIGHT = 34,    // BLUE 
        WARNING = 33,   // YELLOW 
        SUCCESS = 32,   // GREEN 
        ERROR = 31,     // RED
    };

    static Log* GetInstance();

    const static void Print(Type logType, const char* logFormat, ...);

private:
    static Log* m_instance;
};

#endif