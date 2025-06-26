#ifndef ABSTRACTGAMEBASE_H
#define ABSTRACTGAMEBASE_H

class AbstractGameBase
{
public:
    // Initialize the game
    virtual void Init() = 0;

    // Update the game state
    virtual void Update(float deltaTime) = 0;

    // fixed update for collision detections 
    virtual void FixedUpdate(float fixedDeltaTime) = 0; 

    // Render the game
    virtual void Render() = 0;

    // Clean up resources
    virtual void Cleanup() = 0;

protected:
    inline int getWindowWidth() const { return m_windowWidth; }
    inline int getWindowHeight() const { return m_windowHeight; }

private: 
    friend class Engine; 

    int m_windowWidth; 
    int m_windowHeight; 
};  

#endif // ABSTRACTGAMEBASE_H