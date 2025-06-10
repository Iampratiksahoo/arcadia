#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Shader.h"
#include "engine/utilities/Log.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader* shader) : 
    m_shader(shader)
{
    // initialize (and configure) the quad's VAO (Vertex Array Object)
    initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &m_quadVAO);
    
    // delete the shader if it exists
    if(m_shader != nullptr)
    {
        delete m_shader;
        m_shader = nullptr;
    }
}

void SpriteRenderer::DrawSprite(Texture2D &texture, Vector2<float> position, Vector2<float> size, float rotate, Vector3<float> color)
{
    // create glm vectors from the engine vectors 
    glm::vec2 glmPosition = glm::vec2(position.x, position.y);
    glm::vec2 glmSize = glm::vec2(size.x, size.y);
    glm::vec3 glmColor = glm::vec3(color.x, color.y, color.z);

    // load shader 
    m_shader->Use();

    // create a new model
    glm::mat4 model = glm::mat4(1.0f);

    // translate the model to the position
    model = glm::translate(model, glm::vec3(glmPosition, 0.0f));
    
    // rotate the model
    model = glm::translate(model, glm::vec3(0.5f * glmSize.x, 0.5f * glmSize.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * glmSize.x, -0.5f * glmSize.y, 0.0f)); 
    
    // scale the model
    model = glm::scale(model, glm::vec3(glmSize, 1.0f));

    // set the model matrix in the shader
    m_shader->SetMatrix4("model", model);

    // set the color in the shader
    m_shader->SetVector3("spriteColor", glmColor);

    // bind the texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // bind the VAO
    glBindVertexArray(m_quadVAO);

    // draw the quad
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // unbind the VAO
    glBindVertexArray(0);
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
