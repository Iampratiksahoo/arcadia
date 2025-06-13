#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Util/Log.h"

#include <assert.h>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "Component/AbstractComponent.h"
#include "Component/Transform.h"

class GameObject
{
public:
    GameObject();

    virtual void Draw();

#pragma region TEMPLATES
    /// @brief True's if AbstractBaseComponent attached on the GameObject 
    template <typename T>
    bool HasComponent() const
    {
        if( !std::is_base_of<AbstractComponent, T>::value )
        {
            AC_ERROR( "GameObject::Failed To Add component, the component %s is not of type AbstractComponent", typeid(T).name() );
            return false;
        }
        
        bool hasComponent = false;

        for (auto* component : m_components)
        {
            if (dynamic_cast<T*>(component))
            {
                hasComponent = true;
            }
        }

        return hasComponent; 
    }


    /// @brief Returns's an AbstractBaseComponent, if attached to the GameObject
    template <typename T> 
    T* GetComponent()
    {
        if( !std::is_base_of<AbstractComponent, T>::value )
        {
            AC_ERROR( "GameObject::Failed To Add component, the component %s is not of type AbstractComponent", typeid(T).name() );
            return nullptr;
        }

        T* retObject = nullptr;

        for (AbstractComponent* component : m_components)
        {
            if (T* casted = dynamic_cast<T*>(component))
            {
                retObject = casted;
                break;
            }
        }

        return retObject;
    }

    /// @brief Add's an AbstractBaseComponent to the GameObject 
    template <typename T> 
    T* AddComponent()
    {
        if( !std::is_base_of<AbstractComponent, T>::value )
        {
            AC_ERROR( "GameObject::Failed To Add component, the component %s is not of type AbstractComponent", typeid(T).name() );
            return nullptr;
        }

        if( HasComponent<T>() )
        {
            AC_ERROR("GameObject::Failed To add Component because GameObject already has component type %s", typeid(T).name() );
            return nullptr; 
        }

        // create the new component
        T* component = new T();

        // add the component to the list of components 
        addComponentImpl( component );

        // also return this newComponent 
        return component; 
    }

    template <typename T> 
    void AddComponent(T* component)
    {
        if( !std::is_base_of<AbstractComponent, T>::value )
        {
            AC_ERROR( "GameObject::Failed To Add component, the component %s is not of type AbstractComponent", typeid(T).name() );
            return;
        }

        if( component == nullptr )
        {
            AC_ERROR("GameObject::Failed To add Component, because the component was NULL");
            return; 
        }

        if( HasComponent<T>() )
        {
            AC_ERROR("GameObject::Failed To add Component because GameObject already has component type %s", typeid(T).name() );
            return; 
        }

        // add the component to the list of components 
        addComponentImpl( component );
    }
#pragma endregion

private: 
    void addComponentImpl( AbstractComponent* component );

public: 
    Transform* transform; 

private:
    std::vector<AbstractComponent*> m_components;
};

#endif