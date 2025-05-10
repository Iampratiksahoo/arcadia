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