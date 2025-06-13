#include "Input.h"

#include <GLFW/glfw3.h>

// Definition and initialization
bool Input::m_keyLastState[1024] = { false };
bool Input::m_keyState[1024] = { false };

void Input::BeginFrame()
{
    for (int i = 0; i < 1024; ++i)
    {
        m_keyLastState[i] = m_keyState[i];
    }
}

void Input::UpdateKey(int key, int action)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            m_keyState[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_keyState[key] = false;
        }
    }
}

bool Input::GetKey(KeyCode keyCode)
{
    return m_keyState[static_cast<int>(keyCode)];
}

bool Input::GetKeyDown(KeyCode keyCode)
{
    int i = static_cast<int>( keyCode ); 
    return m_keyState[i] && !m_keyLastState[i];
}

bool Input::GetKeyUp(KeyCode keyCode)
{
    int i = static_cast<int>( keyCode ); 
    return !m_keyState[i] && m_keyLastState[i];
}