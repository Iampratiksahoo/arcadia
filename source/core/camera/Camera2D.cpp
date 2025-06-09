#include "Camera2D.h"

Camera2D::Camera2D(float left, float right, float bottom, float top, float zNear, float zFar)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
}

glm::mat4 Camera2D::GetProjectionMatrix() const
{
    return m_projectionMatrix;
}
