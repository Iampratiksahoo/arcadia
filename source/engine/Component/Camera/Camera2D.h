#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "Engine/Component/AbstractComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D : public AbstractComponent
{
public:
    Camera2D(
        float left, 
        float right, 
        float bottom, 
        float top, 
        float zNear = 0.1f, 
        float zFar = 100.0f
    );

    void Reset() override;

    glm::mat4 GetProjectionMatrix() const;

private:
    glm::mat4 m_projectionMatrix;
};

#endif // CAMERA2D_H