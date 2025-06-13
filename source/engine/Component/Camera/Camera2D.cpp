#include "Camera2D.h"

Camera2D::Camera2D(float left, float right, float bottom, float top, float zNear, float zFar)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera2D::Reset()
{
    m_projectionMatrix = glm::ortho( 0.f, 0.f, 0.f, 0.f, .1f, 100.f );
}

glm::mat4 Camera2D::GetProjectionMatrix() const
{
    return m_projectionMatrix;
}
