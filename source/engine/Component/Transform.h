#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "AbstractComponent.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector4.h"

class Transform : public AbstractComponent
{
public: 
    Transform();
    void Reset() override;

    Transform* GetParent();
    void SetParent(Transform* parent);

    Vector3<float> GetPosition(); 
    void SetPosition(Vector3<float> position);

    Vector3<float> GetRotation(); 
    void SetRotation(Vector3<float> rotation);

    Vector3<float> GetScale(); 
    void SetScale(Vector3<float> scale);

    Vector3<float> GetLocalPosition(); 
    void SetLocalPosition(Vector3<float> localPosition);

    Vector3<float> GetLocalRotation(); 
    void SetLocalRotation(Vector3<float> localRotation);

    Vector3<float> GetLocalScale(); 
    void SetLocalScale(Vector3<float> localScale);

    void Translate(Vector3<float> translation);
    void TranslateLocal(Vector3<float> localTranslation);

private:
    void updateWorldParams();
    void updateLocalParams();

private:
    Transform* m_parent; 
    std::vector<Transform*> m_children; 

    Vector3<float> m_position;
    Vector3<float> m_rotation; 
    Vector3<float> m_scale; 

    Vector3<float> m_localPosition;
    Vector3<float> m_localRotation; 
    Vector3<float> m_localScale; 
};

#endif //TRANSFORM_H