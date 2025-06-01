#pragma once

// LOGGING MACROS
#include "utilities/Log.h"

#define AC_LOG(logFormat, ...)			Log::GetInstance()->Print(Log::Type::LOG, logFormat, ##__VA_ARGS__)
#define AC_NOTICE(logFormat, ...)		Log::GetInstance()->Print(Log::Type::HIGHLIGHT, logFormat, ##__VA_ARGS__)
#define AC_WARN(logFormat, ...)			Log::GetInstance()->Print(Log::Type::WARNING, logFormat, ##__VA_ARGS__)
#define AC_SUCCESS(logFormat, ...)		Log::GetInstance()->Print(Log::Type::SUCCESS, logFormat, ##__VA_ARGS__)
#define AC_ERROR(logFormat, ...)		Log::GetInstance()->Print(Log::Type::ERROR, logFormat, ##__VA_ARGS__)

// GLOBALS 
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ASPECT_RATION ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
#define WINDOW_TITLE "Arcadia"

#define OPENGL_VERSION_MAJOR 3
#define OPENGL_VERSION_MINOR 3