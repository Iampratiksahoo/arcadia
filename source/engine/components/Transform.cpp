#include "Transform.h"

Transform::Transform(): 
    position(Vector3<float>::Zero),
    rotation(Vector4<float>::Zero),
    scale(Vector3<float>::Zero)
{
}

void Transform::Reset()
{
    position = Vector3<float>::Zero;
    rotation = Vector4<float>::Zero;
    scale    = Vector3<float>::Zero;
}

void Transform::SetPositionAndRotation(Vector3<float> newPosition, Vector4<float> newRotation)
{
    position = newPosition; 
    rotation = newRotation;
}

void Transform::Translate(Vector3<float> translation)
{
    position += translation;
}