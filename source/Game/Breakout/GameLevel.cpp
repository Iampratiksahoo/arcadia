#include "GameLevel.h"
#include "Brick.h"

void GameLevel::Load(const char *lFile, uint levelWidth, uint levelHeight)
{
    // clear the list of bricks if already present 
    m_bricks.clear();

    // read the level file 
    std::string levelStr = FileHandler::LoadFileFromPath(lFile);

    // now create an array of brick placement from the file 
    std::vector<std::vector<uint>> tileData; 

    std::vector<uint> tileRow; 
    for(char tile : levelStr)
    {
        if (tile >= '0' && tile <= '9') 
        {
            tileRow.push_back(static_cast<uint>(tile - '0'));
        }
        else if (tile == '\n') 
        {
            if (!tileRow.empty()) 
            {
                tileData.push_back(tileRow);
                tileRow.clear();
            }
        }
    }

    // push the last row 
    if (!tileRow.empty()) 
    {
        tileData.push_back(tileRow);
    }

    if( tileData.size() > 0 )
    {
        initLevel( tileData, levelWidth, levelHeight );
    }
} 

void GameLevel::Render()
{
    for(GameObject* brick : m_bricks)
    {
        // we render it only if it is not destroyed!! 
        if( !brick->GetComponent<Brick>()->isDestroyed )
        {
            brick->Render();
        }
    }
}

void GameLevel::initLevel(std::vector<std::vector<uint>> tileData, uint lvlWidth, uint lvlHeight)
{
    // calculate dimensions
    uint height = tileData.size();
    uint width  = tileData[0].size();
    float unitWidth    = lvlWidth / static_cast<float>(width);
    float unitHeight   = lvlHeight / static_cast<float>(height);
    // initialize level tiles based on tileData		
    for (uint y = 0; y < height; ++y)
    {
        for (uint x = 0; x < width; ++x)
        {
            Vector3<float> pos(unitWidth * x, unitHeight * y, 0.f);
            Vector2<float> size(unitWidth, unitHeight);

            // get the tile color from the map
            Vector3<float> tileColor = getColorForTile(tileData[y][x]);

            // initialize the texture to null initially
            Texture2D* texture = nullptr; 

            //set the solid type 
            bool isSolid = false;

            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                texture = &ResourceManager::GetTexture2D("block_soild");
                isSolid = true;
            }
            else if (tileData[y][x] > 1)	    
            {
                texture = &ResourceManager::GetTexture2D("block");
            }

            // if we have a valid texture, then create a gameObject 
            if( texture != nullptr )
            {
                GameObject* brick = constructBrick(
                    pos, 
                    size, 
                    texture, 
                    tileColor, 
                    isSolid 
                ); 
                brick->name = "brick_" + std::to_string(tileData[y][x]);        
                m_bricks.push_back( brick );
            }
        }
    }   
}

Vector3<float> GameLevel::getColorForTile(uint tile)
{
    Vector3<float> color = Vector3<float>(1.f); 

    if( m_tileToColorMap.find(tile) != m_tileToColorMap.end() )
    {
        color = m_tileToColorMap[tile]; 
    }

    return color;
}

GameObject* GameLevel::constructBrick(Vector3<float> position, Vector2<float> size, Texture2D* texture, Vector3<float> color, bool isSolid)
{
    GameObject* obj = new GameObject();  

    // set the position of the gameObject
    obj->transform->SetPosition( position ); 

    SpriteRenderer* renderer = obj->AddComponent<SpriteRenderer>();
    renderer->shader = &ResourceManager::GetShader("core");
    renderer->texture = texture; 
    renderer->color = color;
    renderer->SetSize( size );

    // now add the brick component 
    Brick* brick = obj->AddComponent<Brick>();
    brick->isSolid = isSolid;
    brick->isDestroyed = false; // not destroyed as soon as created

    return obj;
}
