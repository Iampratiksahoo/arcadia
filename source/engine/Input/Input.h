#ifndef INPUT_H
#define INPUT_H

enum class KeyCode; 
class Input
{
    public: 
        static void BeginFrame();
        static void UpdateKey(int key, int action);

        /// @brief True for each frame the Key is kept pressing for 
        static bool GetKey(KeyCode keyCode);      

        /// @brief True for the frame, in which the key was pressed 
        static bool GetKeyDown(KeyCode keyCode);

        /// @brief True for the frame, in which the key was released
        static bool GetKeyUp(KeyCode keyCode);    // released this frame

    private:
        Input() = default;

    private:
        static bool m_keyLastState[1024];
        static bool m_keyState[1024];

};


#endif // INPUT_H