class Texture2D
{
public:
    unsigned int Id; 

    unsigned int Width;
    unsigned int Height;

    unsigned int InternalFormat;
    unsigned int ImageFormat;

    unsigned int WrapS;
    unsigned int WrapT;
    unsigned int FilterMin;
    unsigned int FilterMax;

    Texture2D();

    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};