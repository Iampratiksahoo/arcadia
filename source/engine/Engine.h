#ifndef ENGINE_H
#define ENGINE_H

class Engine
{
    public: 
        Engine(class AbstractGameBase* game);
        ~Engine();

    private:
        void clearScreen();
        
        static void framebufferSizeCallback(struct GLFWwindow* window, int width, int height);
        static void keyCallback(struct GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos); 
        static void cursorEnterCallback(GLFWwindow* window, int entered);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    private:
        class AbstractGameBase* m_game;
        struct GLFWwindow* m_window;

        int m_width;
        int m_height;
        const char* m_title;
        bool m_resizable; 

        float m_fixedDeltaTime;

        float m_deltaTime; 
        float m_lastFrameTime;

        float m_fixedDeltaTimeAccum; 
};

#endif // ENGINE_H