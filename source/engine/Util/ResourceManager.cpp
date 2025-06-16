#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "Lib/stb.h"
#include "glad/glad.h"

#include "FileHandler.h"
#include "Engine/Util/Log.h"
#include "Engine/Core/Texture2D.h"
#include "Engine/Core/Shader.h"

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::m_nameToTexture2DMap;
std::map<std::string, Shader>       ResourceManager::m_nameToShaderMap;

Shader& ResourceManager::LoadShader(std::string name, const char *vShaderFile, const char *fShaderFile)
{
    std::string absoluteVertexShaderPathStr = FileHandler::GetAbsolutePath(vShaderFile);
    std::string absoluteFragmentShaderPathStr = FileHandler::GetAbsolutePath(fShaderFile);

    // if we have a valid shader, store it in the map
    m_nameToShaderMap[name] = loadShaderFromFile( absoluteVertexShaderPathStr.c_str(), absoluteFragmentShaderPathStr.c_str() );

    // return to caller 
    return GetShader( name );
}

Shader& ResourceManager::GetShader(std::string name)
{
    return m_nameToShaderMap[name];
}

Texture2D& ResourceManager::LoadTexture2D(std::string name, const char *tFileName, bool alpha)
{
    std::string absoluteTexturePathStr = FileHandler::GetAbsolutePath( tFileName );

    // if we have a valid texture, store it in the map
    // m_nameToTexture2DMap[name] = loadTextureFromFile( ABSOLUTE_RESOURCES_PATH( tFileName ), alpha);
    m_nameToTexture2DMap.emplace(name, loadTextureFromFile( absoluteTexturePathStr.c_str(), alpha));

    // return to caller
    return GetTexture2D( name );
}

Texture2D& ResourceManager::GetTexture2D(std::string name)
{
    return m_nameToTexture2DMap[name];
}

void ResourceManager::Clear()
{
    // delete all the loaded shaders
    for (auto &shaderPair : m_nameToShaderMap)
    {
        glDeleteProgram(shaderPair.second.id);
    }
   
    // finally clear the shader map
    m_nameToShaderMap.clear();

    // delete all the loaded textures
    for (auto &texturePair : m_nameToTexture2DMap)
    {
        glDeleteTextures(1, &texturePair.second.id);
    }

    // finally clear the Texture map
    m_nameToTexture2DMap.clear();

    AC_SUCCESS("ResourceManager::Cleared all resources from memory");
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile)
{
    // return object 
    Shader shader = Shader();

    // strings that store the actual shader codes
    std::string vertexCode;
    std::string fragmentCode;

    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        // read file's buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // convert stream into string
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();

        // once everything is loaded, not compile shader
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        shader.Compile(vShaderCode, fShaderCode);

        AC_SUCCESS("ResourceManager::Successfully loaded shader from files: %s, %s", vShaderFile, fShaderFile);
    }
    catch (std::ifstream::failure &e)
    {
        AC_ERROR("ResourceManager::ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
    }

    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // return object
    Texture2D texture;

    if(file != nullptr)
    {
        // try to load the texture
        try
        {
            // if alpha is true, we set the internal format to GL_RGBA
            if( alpha )
            {
                texture.internalFormat = GL_RGBA;
                texture.imageFormat = GL_RGBA;
            }

            // then we load the image data using stb_image
            int width, height, nrChannels;
            unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);

            // if we have a valid data
            if(data)
            {
                // generate the texture with the loaded data
                texture.Generate(width, height, data);

                // free the image data
                stbi_image_free(data);

                AC_SUCCESS("ResourceManager::Successfully loaded texture from file %s", file);
            }
        }
        catch (const std::exception &e)
        {
            AC_ERROR("ResourceManager::Failed to load texture from file %s with error: %s", file, e.what());
        }
    }

    return texture;
}