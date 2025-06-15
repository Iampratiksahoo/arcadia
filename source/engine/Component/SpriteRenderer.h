#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "AbstractComponent.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"

#include "Engine/Core/Texture2D.h"
#include "Engine/Core/Shader.h"

class SpriteRenderer : public AbstractComponent
{
    public: 
        SpriteRenderer();
        SpriteRenderer(Shader* shader, Texture2D* texture); 
        ~SpriteRenderer();

        void Reset() override; 
        void Draw( Vector3<float> color = Vector3<float>(1.0f) );

#pragma region INLINE_GETTERS_AND_SETTERS

        /// @brief Set's the size of the Texture to be rendered, provided the Vector2 Param
        inline void SetSize( const Vector2<float> size )
        {
            // set the size
            m_size = size;

            // set the flag to true
            m_isSizeSet = true;
        }

        /// @brief Set's the size of the Texture to be rendered, provided the width and height
        inline void SetSize( float width, float height )
        {
            SetSize(Vector2<float>( width, height ));
        }

        /// @brief Returns the Size of texture, that is being rendered currently. 
        inline Vector2<float> GetSize() const 
        { 
            Vector2<float> size = m_size;

            // if the size is not set, then return the Texture's width and height
            if( !m_isSizeSet && texture != nullptr )
            {
                size = Vector2<float>( texture->width, texture->height );
            }

            return size; 
        }

#pragma endregion

    protected:
        void initRenderData();

    public:
        Shader* shader;
        Texture2D* texture;
    private:
        unsigned int m_quadVAO;

        Vector2<float> m_size; 
        bool m_isSizeSet; // flag to keep track if the size was ever set. 
};
#endif // SPRITE_RENDERER_H