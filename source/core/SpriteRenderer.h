#include "Core.h"  

class SpriteRenderer
{
    public: 
        SpriteRenderer(Shader &shader); 
        ~SpriteRenderer();

        void DrawSprite(
            Texture2D& texture, 
            Vector2<float> position, 
            Vector2<float> size = Vector2<float>(1.0f),
            float rotate = 0.0f, 
            Vector3<float> color = Vector3<float>(1.0f)
        );

    protected:
        void initRenderData();

    private:
        Shader m_shader;
        unsigned int m_quadVAO;
};