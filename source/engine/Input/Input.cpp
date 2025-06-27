#include "Input.h"

#include <GLFW/glfw3.h>
#include "KeyCode.h"

// Definition and initialization
bool Input::m_keyLastState[1024] = { false };
bool Input::m_keyState[1024] = { false };
bool Input::m_mouseInsideWindow = { false }; 
 
Vector2<double> Input::m_mousePos = Vector2<double>::Zero; 

void Input::beginFrame()
{
    for (int i = 0; i < 1024; ++i)
    {
        m_keyLastState[i] = m_keyState[i];
    }
}

void Input::updateKey(int key, int action)
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

void Input::updateMousePos(double mPosX, double mPosY)
{
    m_mousePos.x = mPosX; 
    m_mousePos.y = mPosY; 
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