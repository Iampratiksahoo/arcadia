#include "GameObject.h"

#include "Engine/Component/Transform.h"
#include "Engine/Component/AbstractComponent.h"
#include "Engine/Component/SpriteRenderer.h"

#include "Engine/Util/UUID.h"

GameObject::GameObject() : 
    m_uuid( UUID::GenerateUUID() ) // here we generate an unique UUID for this gameObject
{
    // set the current transfrom of the object
    transform = new Transform(); 

    // assign a default name 
    name = "gameobject_" + m_uuid; 

    // set the object as active in the ctor
    m_isActive = true;

    // add it to the list of components 
    m_components.push_back( transform );
}

void GameObject::Render()
{
    // if the object is active and needs rendering 
    // if there is a valid renderer 
    if( m_isActive )
    {
        if(SpriteRenderer* renderer = GetComponent<SpriteRenderer>())
        {
            renderer->Render();
        }
    }
}

void GameObject::addComponentImpl(AbstractComponent *component)
{
    if( component != nullptr )
    {
        // assign the GameObject to be this
        component->gameObject = this;

        // add to the list of components
        m_components.push_back( component );
    }
}
