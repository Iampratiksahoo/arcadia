#include "Transform.h"
#include <algorithm>

Transform::Transform() :
    m_parent(nullptr),
    m_position(Vector3<float>::Zero),
    m_rotation(Vector3<float>::Zero),
    m_scale(Vector3<float>::One),
    m_localPosition(Vector3<float>::Zero),
    m_localRotation(Vector3<float>::Zero),
    m_localScale(Vector3<float>::One)
{
}

void Transform::Reset()
{
    m_parent = nullptr;
    m_position = Vector3<float>::Zero;
    m_rotation = Vector3<float>::Zero;
    m_scale = Vector3<float>::One;

    m_localPosition = Vector3<float>::Zero;
    m_localRotation = Vector3<float>::Zero;
    m_localScale = Vector3<float>::One;

    m_children.clear();
}

Transform* Transform::GetParent()
{
    return m_parent;
}

void Transform::SetParent(Transform* parent)
{
    if( parent != this )
    {
        if ( m_parent != nullptr )
        {
            auto& siblings = m_parent->m_children;
            siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
        }
    
        m_parent = parent;
    
        if ( m_parent != nullptr )
        {
            m_parent->m_children.push_back(this);
        }
    
        updateLocalParams();
    }
}

Vector3<float> Transform::GetPosition() { return m_position; }
Vector3<float> Transform::GetRotation() { return m_rotation; }
Vector3<float> Transform::GetScale()    { return m_scale; }

Vector3<float> Transform::GetLocalPosition() { return m_localPosition; }
Vector3<float> Transform::GetLocalRotation() { return m_localRotation; }
Vector3<float> Transform::GetLocalScale()    { return m_localScale; }

void Transform::SetPosition(Vector3<float> position)
{
    m_position = position;
    updateLocalParams();
    for (Transform* child : m_children)
        child->updateWorldParams();
}

void Transform::SetRotation(Vector3<float> rotation)
{
    m_rotation = rotation;
    updateLocalParams();
    for (Transform* child : m_children)
        child->updateWorldParams();
}

void Transform::SetScale(Vector3<float> scale)
{
    m_scale = scale;
    updateLocalParams();
    for (Transform* child : m_children)
        child->updateWorldParams();
}

void Transform::SetLocalPosition(Vector3<float> localPosition)
{
    m_localPosition = localPosition;
    updateWorldParams();
}

void Transform::SetLocalRotation(Vector3<float> localRotation)
{
    m_localRotation = localRotation;
    updateWorldParams();
}

void Transform::SetLocalScale(Vector3<float> localScale)
{
    m_localScale = localScale;
    updateWorldParams();
}

void Transform::Translate(Vector3<float> translation)
{
    SetPosition(m_position + translation);
}

void Transform::TranslateLocal(Vector3<float> localTranslation)
{
    SetLocalPosition(m_localPosition + localTranslation);
}

void Transform::updateLocalParams()
{
    if (m_parent)
    {
        m_localPosition = m_position - m_parent->GetPosition();
        m_localRotation = m_rotation - m_parent->GetRotation();
        m_localScale = m_scale / m_parent->GetScale(); // Assume component-wise division is supported
    }
    else
    {
        m_localPosition = m_position;
        m_localRotation = m_rotation;
        m_localScale = m_scale;
    }
}

void Transform::updateWorldParams()
{
    if (m_parent)
    {
        m_position = m_parent->GetPosition() + m_localPosition;
        m_rotation = m_parent->GetRotation() + m_localRotation;
        m_scale = m_parent->GetScale() * m_localScale;
    }
    else
    {
        m_position = m_localPosition;
        m_rotation = m_localRotation;
        m_scale = m_localScale;
    }

    for (Transform* child : m_children)
        child->updateWorldParams();
}