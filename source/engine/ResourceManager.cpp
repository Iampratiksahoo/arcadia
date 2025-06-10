#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "../lib/stb.h"
#include "glad/glad.h"

#include "engine/utilities/Log.h"
#include "Texture2D.h"
#include "Shader.h"

#define PROJECT_PATH "/Users/pratik/Projects/Misc/arcadia/"
#define ABSOLUTE_RESOURCES_PATH(path) (std::string(PROJECT_PATH) + std::string(path)).c_str()

// Instantiate static variables
std::map<const char*, Texture2D>    ResourceManager::m_nameToTexture2DMap;
std::map<const char*, Shader>       ResourceManager::m_nameToShaderMap;

Shader ResourceManager::LoadShader(const char *name, const char *vShaderFile, const char *fShaderFile)
{
    // load the shader from file
    Shader shader = loadShaderFromFile( ABSOLUTE_RESOURCES_PATH( vShaderFile ), ABSOLUTE_RESOURCES_PATH( fShaderFile ));

    // if we have a valid shader, store it in the map
    m_nameToShaderMap[name] = shader;

    // return to caller 
    return shader;
}

Shader ResourceManager::GetShader(const char *name)
{
    return m_nameToShaderMap[name];
}

Texture2D ResourceManager::LoadTexture2D(const char *name, const char *tFileName, bool alpha)
{
    // load the texture from file
    Texture2D texture = loadTextureFromFile( ABSOLUTE_RESOURCES_PATH( tFileName ), alpha);

    // if we have a valid texture, store it in the map
    m_nameToTexture2DMap[name] = texture;

    // return to caller
    return texture;
}

Texture2D ResourceManager::GetTexture2D(const char *name)
{
    return m_nameToTexture2DMap[name];
}

void ResourceManager::Clear()
{
    // delete all the loaded shaders
    for (auto &shaderPair : m_nameToShaderMap)
    {
        glDeleteProgram(shaderPair.second.Id);
    }
   
    // finally clear the shader map
    m_nameToShaderMap.clear();

    // delete all the loaded textures
    for (auto &texturePair : m_nameToTexture2DMap)
    {
        glDeleteTextures(1, &texturePair.second.Id);
    }

    // finally clear the Texture map
    m_nameToTexture2DMap.clear();

    AC_SUCCESS("Cleared all resources from memory");
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

        AC_SUCCESS("Successfully loaded shader from files: %s, %s", vShaderFile, fShaderFile);
    }
    catch (std::ifstream::failure &e)
    {
        AC_ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
    }

    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // return object
    Texture2D texture = Texture2D();

    if(file != nullptr)
    {
        // try to load the texture
        try
        {
            // if alpha is true, we set the internal format to GL_RGBA
            if( alpha )
            {
                texture.InternalFormat = GL_RGBA;
                texture.ImageFormat = GL_RGBA;
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

                AC_SUCCESS("Successfully loaded texture from file %s", file);
            }
        }
        catch (const std::exception &e)
        {
            AC_ERROR("Failed to load texture from file %s with error: %s", file, e.what());
        }
    }

    return texture;
}
