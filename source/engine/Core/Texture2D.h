#ifndef TEXTURE2D_H
#define TEXTURE2D_H
class Texture2D
{
public:
    unsigned int id; 

    unsigned int width;
    unsigned int height;

    unsigned int internalFormat;
    unsigned int imageFormat;

    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;

    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};

#endif