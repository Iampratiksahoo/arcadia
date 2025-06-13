#include "GameObject.h"

#include "engine/components/Transform.h"
#include "engine/components/AbstractComponent.h"
#include "engine/components/SpriteRenderer.h"

GameObject::GameObject()
{
    // set the current transfrom of the object
    transform = new Transform(); 

    // add it to the list of components 
    m_components.push_back( transform );
}

void GameObject::Draw()
{
    if( SpriteRenderer* renderer = GetComponent<SpriteRenderer>() )
    {
        renderer->Draw();
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
