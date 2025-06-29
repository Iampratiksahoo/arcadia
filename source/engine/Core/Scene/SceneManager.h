#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "vector"
#include "string"
#include "unordered_set"
#include "Scene.h"
#include "Engine/AbstractSystemManager.h"

class SceneManager : public AbstractSystemManager,  public SingletonBase<SceneManager> 
{
public: 
    SceneManager() = default; 
    void SetActiveScene( Scene* scene );
    Scene* GetActiveScene(); 

private: 
    friend class Engine; 
    friend class Scene; 

    void gameStart() override;
    void update(float deltaTime) override;
    void fixedUpdate(float fixedDeltaTime) override;
    void render() override;
    void cleanup() override;

    void addScene( Scene* scene );

    std::unordered_set<std::string> m_sceneUUIDs;
    std::vector<Scene*> m_scenes;
    Scene* m_activeScene; 
}; 

#endif // SCENEMANAGER_H