#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <assert.h>
#include <type_traits>
#include <vector>

class Transform; 
class AbstractComponent;
class GameObject
{
public:
    GameObject();

#pragma region TEMPLATES
    /// @brief True's if AbstractBaseComponent attached on the GameObject 
    template <typename T>
    bool HasComponent() const
    {
        assert((std::is_base_of<AbstractComponent, T>::value));
        
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
        assert(( std::is_base_of<AbstractComponent, T>::value ));

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
    void AddComponent()
    {
        assert(( std::is_base_of<AbstractComponent, T>::value )
                && HasComponent<T>() );

        // create the new component
        T* newComponent = new T();

        // add to the list of components
        m_components.push_back( newComponent );
    }
#pragma endregion

public: 
    Transform* transform; 

private:
    std::vector<AbstractComponent*> m_components;
};

#endif