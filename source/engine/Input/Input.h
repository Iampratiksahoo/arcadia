#ifndef INPUT_H
#define INPUT_H

#include "Engine/Math/Vector2.h"

enum class KeyCode; 
class Input
{    
    public: 
        /// @brief True for each frame the Key is kept pressing for 
        static bool GetKey(KeyCode keyCode);      

        /// @brief True for the frame, in which the key was pressed 
        static bool GetKeyDown(KeyCode keyCode);

        /// @brief True for the frame, in which the key was released
        static bool GetKeyUp(KeyCode keyCode);    // released this frame

        /// @brief Returns the current mouse position 
        inline static Vector2<double> GetMousePosition() { return m_mousePos; };

        /// @brief Returns tru when mouse is inside window  
        inline static bool IsMouseInsideWindow() { return m_mouseInsideWindow; }; 

    private:
        Input() = default;

        friend class Engine; 

        static void beginFrame();
        static void updateKey(int key, int action);
        static void updateMousePos(double mPosX, double mPosY);

    private:
        static bool m_keyLastState[1024];
        static bool m_keyState[1024];

        static bool m_mouseInsideWindow; 
        static Vector2<double> m_mousePos;
};


#endif // INPUT_H