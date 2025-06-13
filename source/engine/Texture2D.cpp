#include "Texture2D.h"

#include <glad/glad.h>
#include "Engine/Util/Log.h"

Texture2D::Texture2D() : 
    width(0), 
    height(0), 
    internalFormat(GL_RGB), 
    imageFormat(GL_RGB), 
    wrapS(GL_REPEAT),
    wrapT(GL_REPEAT), 
    filterMin(GL_LINEAR),
    filterMax(GL_LINEAR)
{
    glGenTextures(1, &id);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char *data)
{
    this->width = width;
    this->height = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    unsigned int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        AC_ERROR("OpenGL error after glTexImage2D: %d", error);
    }
    
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}
