#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include "Core.h"

void Shader::Compile(const char *vShaderCode, const char *fShaderCode)
{
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // shader Program
    Id = glCreateProgram();
    glAttachShader(Id, vertex);
    glAttachShader(Id, fragment);
    glLinkProgram(Id);
    checkCompileErrors(Id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);    
}

Shader &Shader::Use()
{
    glUseProgram(Id);
    return *this;
}

void Shader::SetBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(Id, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(Id, name), value);
}

void Shader::SetVec2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(Id, name), 1, &value[0]);
}
void Shader::SetVec2(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(Id, name), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(Id, name), 1, &value[0]);
}
void Shader::SetVec3(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(Id, name), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(Id, name), 1, &value[0]);
}
void Shader::SetVec4(const char* name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(Id, name), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const char* name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const char* name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const char* name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, const char* type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") 
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            AC_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- ", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            AC_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n -- --------------------------------------------------- -- ", type, infoLog);
        }
    }
}
