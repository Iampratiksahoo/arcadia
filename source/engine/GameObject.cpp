#include "GameObject.h"

#include "engine/components/Transform.h"
#include "engine/components/AbstractComponent.h"

GameObject::GameObject()
{
    // set the current transfrom of the object
    transform = new Transform(); 

    // add it to the list of components 
    m_components.push_back( transform );
}