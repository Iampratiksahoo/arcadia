#ifndef SHADER_H
#define SHADER_H

#include "engine/maths/Vector2.h"
#include "engine/maths/Vector3.h"
#include "engine/maths/Vector4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
    // the program ID
    unsigned int id;

public:
    Shader() = default;
    Shader(const Shader& shader) ;

    /// <summary>
    /// Compiles the shader from the given vertex and fragment shader code
    /// </summary>
    void Compile(const char *vShaderCode, const char *fShaderCode);
    
    /// <summary>
    /// Activates the shader
    /// </summary>
    Shader* Use();

    /// <summary>
    /// Sets the boolean parameter for a shader
    /// </summary>
    void SetBoolean(const char* name, bool value) const;

    /// <summary>
    /// Sets the integer parameter for a shader
    /// </summary>
    void SetInteger(const char* name, int value) const;

    /// <summary>
    /// Sets the float parameter for a shader
    /// </summary>
    void SetFloat(const char* name, float value) const;

    void SetVector2(const char* name, const glm::vec2& value) const;
    void SetVector2(const char* name, const Vector2<float>& value) const;
    void SetVector2(const char* name, float x, float y) const;

    void SetVector3(const char* name, const glm::vec3& value) const;
    void SetVector3(const char* name, const Vector3<float>value) const;
    void SetVector3(const char* name, float x, float y, float z) const;

    void SetVector4(const char* name, const glm::vec4& value) const;
    void SetVector4(const char* name, const Vector4<float>& value) const;
    void SetVector4(const char* name, float x, float y, float z, float w) const;

    void SetMatrix2(const char* name, const glm::mat2& mat) const;
    void SetMatrix3(const char* name, const glm::mat3& mat) const;
    void SetMatrix4(const char* name, const glm::mat4& mat) const;

private:
    void checkCompileErrors(unsigned int shader, const char* type);
};

#endif