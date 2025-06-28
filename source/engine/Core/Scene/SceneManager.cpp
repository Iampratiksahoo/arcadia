#include "SceneManager.h"
#include "Engine/Util/Core.h"

std::unordered_set<std::string> SceneManager::m_sceneUUIDs;
std::vector<Scene*> SceneManager::m_scenes;
Scene* SceneManager::m_activeScene = nullptr; 

void SceneManager::SetActiveScene(Scene *scene)
{
    if(scene != nullptr)
    {
        auto it = std::find(m_scenes.begin(), m_scenes.end(), scene);
        if (it != m_scenes.end()) 
        {
            m_activeScene = *it; 
        }
        else 
        {
            AC_ERROR("SceneManager::SetActiveScene() Failed to set active scene. Scene with name '%s' not in the Scene list", scene->name.c_str());
        }
    }
}

Scene *SceneManager::GetActiveScene()
{
    // if we don't have an active scene 
    // make the first scene in the list as active 
    if(m_activeScene == nullptr)
    {
        if(m_scenes.size() > 0)
        {
            m_activeScene = m_scenes[0]; 
        }
        else 
        {
            AC_ENGINE_FORCE_KILL("SceneManager::GetActiveScene() Unable to set active scene, scenes list is empty.");
        }
    }

    return m_activeScene; 
}

void SceneManager::gameStart()
{
    if( Scene* activeScene = GetActiveScene() )
    {
        activeScene->gameStart();
    }
}

void SceneManager::update(float deltaTime)
{
    if( Scene* activeScene = GetActiveScene() )
    {
        activeScene->update(deltaTime); 
    }
}

void SceneManager::fixedUpdate(float fixedDeltaTime)
{
    if( Scene* activeScene = GetActiveScene() )
    {
        activeScene->fixedUpdate(fixedDeltaTime); 
    }
}

void SceneManager::render()
{
    if( Scene* activeScene = GetActiveScene() )
    {
        activeScene->render();
    }
}

void SceneManager::addScene(Scene *scene)
{
    if(scene != nullptr)
    {
        const std::string& uuid = scene->GetUuid();

        if (m_sceneUUIDs.find(uuid) == m_sceneUUIDs.end()) 
        {
            m_scenes.push_back(scene);
            m_sceneUUIDs.insert(uuid);
        }
    }
}

void SceneManager::cleanup()
{
    for(Scene* scene : m_scenes)
    {
        if(scene != nullptr)
        {
            delete scene; 
        }
    }
}