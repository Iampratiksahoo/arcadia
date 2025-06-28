#ifndef SCENE_H
#define SCENE_H

#include "vector"
#include "unordered_set"
#include "string"

class GameObject; 
class Scene
{
public:
    Scene();

    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* GameObject);
    void MoveGameObjectToIndex(GameObject* gameObject, size_t targetIndex);


    inline const std::string& GetUuid() const { return m_uuid; }

protected:
    friend class SceneManager; 

    ~Scene();

private:

    void gameStart();
    void update(float deltaTime);
    void fixedUpdate(float fixedDeltaTime);
    void render();

private:
    std::unordered_set<std::string> m_gameObjectUUIDs;
    std::vector<GameObject*> m_gameObjects;

    std::string m_uuid; 
    std::string name; 
};

#endif // SCENE_H