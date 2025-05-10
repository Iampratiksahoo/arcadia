class Game
{
    public: 
        enum class State
        {
            None = 0,
            Active,
            Menu,
            Win,
        };

        Game();
        ~Game();

    protected:
        void Init();
        void ProcessInput(float deltaTime);
        void Update(float deltaTime);
        void Render();

    private:
        struct GLFWwindow* m_window;

        int m_width;
        int m_height;
        const char* m_title;

        float m_deltaTime; 
        float m_lastFrameTime;

        State m_state;	
        bool m_keys[1024];
};