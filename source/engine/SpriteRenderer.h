#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "engine/maths/Vector2.h"
#include "engine/maths/Vector3.h"

class Texture2D;
class Shader; 
class SpriteRenderer
{
    public: 
        SpriteRenderer(Shader* shader); 
        ~SpriteRenderer();

        void DrawSprite(
            Texture2D& texture, 
            Vector2<float> position, 
            Vector2<float> size = Vector2<float>(10.f),
            float rotate = 0.0f, 
            Vector3<float> color = Vector3<float>(1.0f)
        );

    protected:
        void initRenderData();

    private:
        Shader* m_shader;
        unsigned int m_quadVAO;
};
#endif // SPRITE_RENDERER_H