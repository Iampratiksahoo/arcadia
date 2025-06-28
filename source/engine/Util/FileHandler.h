#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler
{
public: 
    static std::string LoadFileFromPath( const char* path );

    static inline std::string GetAbsolutePath(const std::string& path) 
    {
        return std::string(PROJECT_ROOT_DIR) + "/" + path;
    }

}; 

#endif