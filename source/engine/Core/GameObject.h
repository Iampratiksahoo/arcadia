#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Util/Log.h"

#include <assert.h>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <string> 

#include "Engine/Component/Core.h"

class GameObject
{
public:
    GameObject(); 

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

    template <typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<AbstractComponent, T>::value,
                    "GameObject::RemoveComponent only works with types derived from AbstractComponent");

        for (auto it = m_components.begin(); it != m_components.end(); ++it)
        {
            if (T* casted = dynamic_cast<T*>(*it))
            {
                if (casted == transform)
                {
                    AC_ERROR("GameObject::Cannot remove Transform component");
                    return;
                }

                // if component IS-A AbstractCollider, the register it to the CollisionManager
                if(AbstractCollider* asCollider = dynamic_cast<AbstractCollider*>(casted))
                {
                    CollisionManager::GetInstance()->removeCollider( asCollider );
                }

                // finally delete it 
                delete *it;
                m_components.erase(it);
                return;
            }
        }

        AC_WARN("GameObject::RemoveComponent called, but component of type %s not found", typeid(T).name());
    }


    inline const std::string& GetUuid() const { return m_uuid; }

    inline bool IsActive() const { return m_isActive; }
    void SetActive(bool isActive);
#pragma endregion

protected:
    friend class Scene; 
    friend class CollisionManager;

    ~GameObject(); 

private: 
    void gameStart();
    void update(float deltaTime);
    void fixedUpdate(float fixedDeltaTime);
    void onCollisionEnter(class AbstractCollider* other);
    void render();
    
    void addComponentImpl( AbstractComponent* component );

public: 
    Transform* transform; 
    std::string name; 

private:
    std::string m_uuid; 
    bool m_isActive; // will it be rendered 
    std::vector<AbstractComponent*> m_components;
};

#endif