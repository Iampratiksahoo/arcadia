#include "SpriteRenderer.h"
#include "Engine/GameObject.h"
#include "Engine/Texture2D.h"
#include "Engine/Shader.h"
#include "Engine/Util/Log.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer() : SpriteRenderer( nullptr, nullptr )
{
}

SpriteRenderer::SpriteRenderer(Shader *shader, Texture2D* texture) : 
    m_size(10.f),
    shader( shader ), 
    texture( texture )

{
    // initialize (and configure) the quad's VAO (Vertex Array Object)
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    Reset();
}

void SpriteRenderer::Reset()
{
    glDeleteVertexArrays(1, &m_quadVAO);
    
    // delete the shader if it exists
    if(shader != nullptr)
    {
        delete shader;
        shader = nullptr;
    }

    // delete the texture if it exists 
    if( texture != nullptr )
    {
        delete texture; 
        texture = nullptr;
    }
}

void SpriteRenderer::Draw( Vector3<float> color )
{
    // if either of shader or texture is null, then do not render
    if( shader != nullptr &&  texture != nullptr )
    {
        // fetch/calculate the pre-requisites 
        Transform* transform = gameObject->transform;
        Vector3<float> position = transform->position;
        float rotationInRadians = transform->rotation.Magnitude();
        Vector3<float> rotationAxis = transform->rotation.GetNormalized();
        Vector2<float> size = Vector2<float>( texture->width, texture->height );
        
        // if we have a size explicitly set for this Sprite, then set that instead
        if( m_isSizeSet )
        {
            size = m_size;
        }

        // safe check for the rotation
        if( rotationAxis == Vector3<float>::Zero )
        {
            rotationAxis = Vector3<float>(.0f, .0f, 1.f);
        }

        // create glm vectors from the engine vectors 
        glm::vec2 glmPosition = glm::vec2( position.x, position.y );
        glm::vec2 glmSize = glm::vec2(size.x, size.y);
        glm::vec3 glmColor = glm::vec3(color.x, color.y, color.z);
        glm::vec3 glmRotAxis = glm::vec3( rotationAxis.x, rotationAxis.y, rotationAxis.z );

        // load shader 
        shader->Use();

        // create a new model
        glm::mat4 model = glm::mat4(1.0f);

        // translate the model to the position
        model = glm::translate(model, glm::vec3(glmPosition, 0.0f));
        
        // rotate the model
        model = glm::translate( model, glm::vec3(0.5f * glmSize.x, 0.5f * glmSize.y, 0.0f) ); 
        model = glm::rotate( model, rotationInRadians, glmRotAxis );
        model = glm::translate( model, glm::vec3(-0.5f * glmSize.x, -0.5f * glmSize.y, 0.0f) ); 
        
        // scale the model
        model = glm::scale(model, glm::vec3(glmSize, 1.0f));

        // set the model matrix in the shader
        shader->SetMatrix4("model", model);

        // set the color in the shader
        shader->SetVector3("spriteColor", glmColor);

        // bind the texture
        glActiveTexture(GL_TEXTURE0);
        texture->Bind();

        // bind the VAO
        glBindVertexArray(m_quadVAO);

        // draw the quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // unbind the VAO
        glBindVertexArray(0);
    }
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;

    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    
    // generates a Vertex Array Object (VAO) and a Vertex Buffer Object (VBO).
    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &VBO);

    // Binds the VBO and uploads the vertex data to the GPU.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Binds the VAO so it remembers the following settings. 
    glBindVertexArray(m_quadVAO);

    // Enables the first attribute (location 0) for the shader.
    glEnableVertexAttribArray(0);

    // Tells OpenGL how to read the data:
    // Each vertex is 4 floats (position + texcoord).
    // No gaps between attributes (stride is 4 floats).
    // Data starts at the beginning of the array.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // Unbinds the VBO and VAO to avoid accidental changes.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
