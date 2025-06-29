#include "Scene.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Util/UUID.h"
#include "SceneManager.h"

Scene::Scene() : 
    m_uuid( UUID::GenerateUUID() )
{
    SceneManager::GetInstance()->addScene( this );
}

Scene::~Scene()
{
    for(GameObject* gameObject : m_gameObjects)
    {
        if(gameObject != nullptr)
        {
            delete gameObject; 
        }
    }
}

void Scene::gameStart()
{
    for(GameObject* gameObject : m_gameObjects)
    {
        if(gameObject != nullptr)
        {
            gameObject->gameStart(); 
        }
    }
}

void Scene::update(float deltaTime)
{
    for(GameObject* gameObject : m_gameObjects)
    {
        if(gameObject != nullptr)
        {
            gameObject->update(deltaTime); 
        }
    }
}

void Scene::fixedUpdate(float fixedDeltaTime)
{
    for(GameObject* gameObject : m_gameObjects)
    {
        if(gameObject != nullptr)
        {
            gameObject->fixedUpdate(fixedDeltaTime);
        }
    }
}

void Scene::render()
{
    for(GameObject* gameObject : m_gameObjects)
    {
        if(gameObject != nullptr)
        {
            gameObject->render(); 
        }
    }
}

void Scene::AddGameObject(GameObject *gameObject)
{
    if(gameObject != nullptr)
    {
        const std::string& uuid = gameObject->GetUuid();

        if (m_gameObjectUUIDs.find(uuid) == m_gameObjectUUIDs.end()) 
        {
            m_gameObjects.push_back(gameObject);
            m_gameObjectUUIDs.insert(uuid);
        }
    }
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
    if(gameObject != nullptr)
    {
        const std::string& uuid = gameObject->GetUuid();
        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        if (it != m_gameObjects.end()) 
        {
            m_gameObjects.erase(it);
            m_gameObjectUUIDs.erase(uuid);
        }
    }
}

void Scene::MoveGameObjectToIndex(GameObject* gameObject, size_t targetIndex)
{
    if (gameObject != nullptr) 
    {
        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        if (it != m_gameObjects.end()) 
        {
            if (targetIndex < m_gameObjects.size()) 
            {
                GameObject* foundGameObject = *it;
                
                // Remove from current position
                m_gameObjects.erase(it);
                
                // Insert at the new target position
                m_gameObjects.insert(m_gameObjects.begin() + targetIndex, foundGameObject);
                
                AC_NOTICE("Scene::MoveGameObjectToIndex() Moved gameObject '%s' to index %zu", gameObject->name.c_str(), targetIndex);
            }
            else
            {
                AC_ERROR("Scene::MoveGameObjectToIndex() Target index %zu out of range", targetIndex);
            }
        }
        else
        {
            AC_ERROR("Scene::MoveGameObjectToIndex() GameObject not found in m_gameObjects");
        }
    }
    else
    {
        AC_ERROR("Scene::MoveGameObjectToIndex() Called with null gameObject");
    }
}