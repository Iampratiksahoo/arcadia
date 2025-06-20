#include "FileHandler.h"

#include <fstream>
#include <sstream>
#include <string>
#include "Log.h"

std::string FileHandler::LoadFileFromPath(const char* path)
{
    // construct the absolute path before attempting load the file
    std::string absolutePathStr = GetAbsolutePath(path);
    const char* absolutePath = absolutePathStr.c_str();

    // string to store the actual loaded file data 
    std::string loadedFile;

    try
    {
        std::ifstream file(absolutePath);
        if (!file.is_open()) 
        {
            throw std::ifstream::failure("File not found or cannot be opened.");
        }

        std::stringstream fileStream;

        fileStream << file.rdbuf();
        file.close();

        loadedFile = fileStream.str();
        AC_SUCCESS("FileHandler::Successfully loaded file from path: %s", absolutePath);
    }
    catch (std::ifstream::failure& e)
    {
        AC_ERROR("FileHandler::Failed to load file from path '%s' | Error: %s", absolutePath, e.what());
    }

    return loadedFile;
}
