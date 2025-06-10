#include "Input.h"

#include "engine/KeyCode.h"
#include <GLFW/glfw3.h>

// Definition and initialization
bool Input::m_keys[1024] = { false };

void Input::UpdateKey(int key, int action)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            m_keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_keys[key] = false;
        }
    }
}

bool Input::IsKeyDown(KeyCode keyCode)
{
    return m_keys[static_cast<int>(keyCode)];
}
