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

        int m_width;
        int m_height;
        const char* m_title;

        float m_deltaTime; 
        float m_lastFrameTime;

        State m_state;	
        bool m_keys[1024];
};