#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "vector"
#include "string"
#include "unordered_set"
#include "Scene.h"

class SceneManager
{
public: 
    static void SetActiveScene( Scene* scene );
    static Scene* GetActiveScene(); 

private: 
    friend class Engine; 
    friend class Scene; 

    SceneManager() = default; 

    static void gameStart();
    static void update(float deltaTime);
    static void fixedUpdate(float fixedDeltaTime);
    static void render();
    static void cleanup();

    static void addScene( Scene* scene );

    static std::unordered_set<std::string> m_sceneUUIDs;
    static std::vector<Scene*> m_scenes;
    static Scene* m_activeScene; 
}; 

#endif // SCENEMANAGER_H