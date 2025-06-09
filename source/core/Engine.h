#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
    public: 
        enum class State
        {
            None = 0,
            Active,
            Menu,
            Win,
        };

        Engine(class IGame& game);
        ~Engine();

    protected:
        void ClearScreen();

    private:
        static void framebufferSizeCallback(struct GLFWwindow* window, int width, int height);
        static void keyCallback(struct GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        class IGame& m_game;
        struct GLFWwindow* m_window;

        // these are require to be static 
        static int m_width;
        static int m_height;
        static const char* m_title;

        float m_deltaTime; 
        float m_lastFrameTime;

        State m_state;	
};

#endif // ENGINE_H