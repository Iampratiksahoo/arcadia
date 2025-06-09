#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core.h"

Shader::Shader(const Shader &shader)
{
    Id = shader.Id;
}

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

void Shader::SetBoolean(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(Id, name), (int)value);
}

void Shader::SetInteger(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(Id, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(Id, name), value);
}

void Shader::SetVector2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::SetVector2(const char *name, const Vector2<float> &value) const
{
    SetVector2(name, value.x, value.y);
}

void Shader::SetVector2(const char *name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(Id, name), x, y);
}

// ------------------------------------------------------------------------
void Shader::SetVector3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::SetVector3(const char *name, const Vector3<float> value) const
{
    SetVector3(name, value.x, value.y, value.z);
}

void Shader::SetVector3(const char *name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(Id, name), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVector4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(Id, name), 1, &value[0]);
}

void Shader::SetVector4(const char *name, const Vector4<float> &value) const
{
    SetVector4(name, value.x, value.y, value.z, value.w);
}

void Shader::SetVector4(const char *name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(Id, name), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix2(const char* name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix3(const char* name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Id, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMatrix4(const char* name, const glm::mat4& mat) const
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
