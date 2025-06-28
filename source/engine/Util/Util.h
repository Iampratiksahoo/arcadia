#ifndef UTIL_H
#define UTIL_H

#include "Log.h"

#define AC_ENGINE_FORCE_KILL(LogFormat, ...)  \
    do {                                \
        AC_ERROR(LogFormat, ##__VA_ARGS__); \
        std::terminate();               \
    } while (0)


class Util
{

};

#endif // UTIL_H