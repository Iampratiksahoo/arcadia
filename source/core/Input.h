class Input
{
    public: 
        static void UpdateKey(int key, int action);

    private:
        Input() = default;

    private:
        static bool m_keys[1024];

};