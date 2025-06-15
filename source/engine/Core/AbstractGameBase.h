#ifndef ABSTRACTGAMEBASE_H
#define ABSTRACTGAMEBASE_H

class AbstractGameBase
{
public:
    // Initialize the game
    virtual void Init() = 0;

    // Handle input events
    virtual void ProcessInput(float deltaTime) = 0;

    // Update the game state
    virtual void Update(float deltaTime) = 0;

    // Render the game
    virtual void Render() = 0;

    // Clean up resources
    virtual void Cleanup() = 0;
};

#endif // ABSTRACTGAMEBASE_H