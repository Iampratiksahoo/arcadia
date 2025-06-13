#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "AbstractComponent.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector4.h"

template <typename T> 
class Vector3; 

template <typename T>
class Vector4;

class Transform : public AbstractComponent
{
public: 
    Transform();
    void Reset() override;
    void SetPositionAndRotation(Vector3<float> newPosition, Vector3<float> newRotation);
    void Translate(Vector3<float> translation);

public:
    Vector3<float> position;
    Vector3<float> rotation; 
    Vector3<float> scale; 
};

#endif //TRANSFORM_H