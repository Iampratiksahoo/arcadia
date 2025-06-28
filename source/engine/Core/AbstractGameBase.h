#ifndef ABSTRACTGAMEBASE_H
#define ABSTRACTGAMEBASE_H

class AbstractGameBase
{
public:
    /// @brief Called when the game is initialized initially 
    virtual void Init() = 0;

    virtual const char* GetIniPath() = 0;

    /// @brief called when the game is cleaned up, post game completion. 
    virtual void Cleanup() = 0;

protected:
    inline int getWindowWidth() const { return m_windowWidth; }
    inline int getWindowHeight() const { return m_windowHeight; }

private: 
    friend class Engine; 

    int m_windowWidth; 
    int m_windowHeight; 
};  

#endif // ABSTRACTGAMEBASE_H