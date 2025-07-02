#include "GameObject.h"
#include "Scene/SceneManager.h"

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

    // add this to the current scene 
    SceneManager::GetInstance()->GetActiveScene()->AddGameObject( this );

    // add it to the list of components 
    addComponentImpl( transform );
}

GameObject::~GameObject()
{
    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            delete component; 
        }
    }
}

void GameObject::gameStart()
{
    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            component->OnGameStart();
        }
    }
}

void GameObject::update(float deltaTime)
{
    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            component->Update( deltaTime );
        }
    }
}

void GameObject::fixedUpdate(float fixedDeltaTime)
{
    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            component->FixedUpdate( fixedDeltaTime );
        }
    }
}

void GameObject::onCollisionEnter(AbstractCollider *other)
{
    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            component->OnCollisionEnter( other );
        }
    }
}

void GameObject::render()
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

void GameObject::SetActive(bool isActive)
{
    m_isActive = isActive; 

    for( AbstractComponent* component : m_components )
    {
        if(component != nullptr)
        {
            component->OnActiveStateChange( m_isActive );
        }
    }
}

void GameObject::addComponentImpl(AbstractComponent *component)
{
    if( component != nullptr )
    {
        // assign the GameObject to be this
        component->gameObject = this;

        // if component IS-A Transform, assign directly
        if (Transform* asTransform = dynamic_cast<Transform*>(component))
        {
            component->transform = asTransform;
        }
        else
        {
            // Otherwise, get the existing Transform from this GameObject
            component->transform = GetComponent<Transform>();
        }

        // if component IS-A AbstractCollider, the register it to the CollisionManager
        if(AbstractCollider* asCollider = dynamic_cast<AbstractCollider*>(component))
        {
            CollisionManager::GetInstance()->addCollider( asCollider );
        }

        // add to the list of components
        m_components.push_back( component );
    }
}
