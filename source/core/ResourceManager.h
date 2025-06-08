#include <map>

class Shader;
class Texture2D;
class ResourceManager
{
public:
    /// @brief Load a shader given the vertex and fragment shader filenames.
    static Shader LoadShader(const char* name, const char* vShaderFile, const char* fShaderFile);

    /// @brief Get a Shader by name. 
    static Shader GetShader(const char* name);

    /// @brief Load a Texture2D given the texture filename.
    static Texture2D LoadTexture2D(const char* name, const char* tFileName, bool alpha );

    /// @brief Get a Texture2D by name. 
    static Texture2D GetTexture2D(const char* name);

    /// @brief Clear all the loaded resources from the memory. 
    static void Clear();

private:
    // resource storage
    static std::map<std::string, Shader>    m_nameToShaderMap;
    static std::map<std::string, Texture2D> m_nameToTexture2DMap;

    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char *file, bool alpha);
};
