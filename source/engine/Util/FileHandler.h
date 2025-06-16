#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

#define ABSOLUTE_FILE_PATH(path) (std::string(PROJECT_ROOT_DIR) + std::string(path))    

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