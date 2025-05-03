#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // the program ID
    unsigned int ID;

public:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    
    /// <summary>
    /// Activates the shader
    /// </summary>
    void Use();

    /// <summary>
    /// Sets the boolean parameter for a shader
    /// </summary>
    void SetBool(const char* name, bool value) const;

    /// <summary>
    /// Sets the integer parameter for a shader
    /// </summary>
    void SetInt(const char* name, int value) const;

    /// <summary>
    /// Sets the float parameter for a shader
    /// </summary>
    void SetFloat(const char* name, float value) const;

    void SetVec2(const char* name, const glm::vec2& value) const;
    void SetVec2(const char* name, float x, float y) const;
    void SetVec3(const char* name, const glm::vec3& value) const;
    void SetVec3(const char* name, float x, float y, float z) const;
    void SetVec4(const char* name, const glm::vec4& value) const;
    void SetVec4(const char* name, float x, float y, float z, float w) const;
    void SetMat2(const char* name, const glm::mat2& mat) const;
    void SetMat3(const char* name, const glm::mat3& mat) const;
    void SetMat4(const char* name, const glm::mat4& mat) const;
    void checkCompileErrors(unsigned int shader, const char* type);

};

#endif