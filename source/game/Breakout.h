#include "engine/Core.h" 

class Breakout : public IGame
{
public:
    Breakout();
    ~Breakout();
    
    // Initialize the game
    void Init() override;

    // Handle input events
    void ProcessInput(float deltaTime) override;

    // Update the game state
    void Update(float deltaTime) override;

    // Render the game
    void Render() override;

    // Clean up resources
    void Cleanup() override;

private:
    class SpriteRenderer* m_renderer;

    Vector2<float> m_position; 

    int m_width; 
    int m_height; 
};