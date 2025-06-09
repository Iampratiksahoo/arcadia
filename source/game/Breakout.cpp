#include "Breakout.h"

Breakout::Breakout() :
    m_position(200.f),
    m_renderer(nullptr),
    m_width(WINDOW_WIDTH), 
    m_height(WINDOW_HEIGHT)
{

}

Breakout::~Breakout()
{
    if(m_renderer != nullptr)
    {
        delete m_renderer;
    }
}

// Initialize the game
void Breakout::Init()
{
}

// Handle input events
void Breakout::ProcessInput(float deltaTime)
{

}

// Update the game state
void Breakout::Update(float deltaTime)
{
}

// Render the game
void Breakout::Render()
{
}

// Clean up resources
void Breakout::Cleanup()
{
}