#ifndef INPUT_H
#define INPUT_H

#include "Core.h"

class Input
{
    public: 
        static void UpdateKey(int key, int action);

        /// @brief True if Key is pressed
        static bool IsKeyDown(KeyCode keyCode);

    private:
        Input() = default;

    private:
        static bool m_keys[1024];

};


#endif // INPUT_H