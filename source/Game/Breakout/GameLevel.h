#pragma once
#include <Engine/Core.h>

class GameLevel 
{
public:
    void Load(const char* lFile, uint levelWidth, uint levelHeight); 
    void Render();

    inline std::vector<GameObject*> GetBricks() const { return m_bricks; }

private:
    void initLevel( std::vector<std::vector<uint>> tileData, uint lvlWidth, uint lvlHeight );
    Vector3<float> getColorForTile(uint tile); 
    GameObject* constructBrick(Vector3<float> position, Vector2<float> size, Texture2D* texture, Vector3<float> color, bool isSolid);

private:
    std::vector<GameObject*> m_bricks;
    std::map<uint, Vector3<float>> m_tileToColorMap
    {
        {1, Vector3<float>(0.8f, 0.8f, 0.7f)},
        {2, Vector3<float>(0.2f, 0.6f, 1.0f)},
        {3, Vector3<float>(0.0f, 0.7f, 0.0f)},
        {4, Vector3<float>(0.8f, 0.8f, 0.4f)},
        {5, Vector3<float>(1.0f, 0.5f, 0.0f)}
    };
};