#ifndef SINGLETONBASE_H
#define SINGLETONBASE_H

#pragma once

template <typename T>
class SingletonBase
{
public:
    static T* GetInstance()
    {
        static T instance;  // Meyers singleton: no manual allocation, no leaks.
        return &instance;
    }

    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
    SingletonBase(SingletonBase&&) = delete;
    SingletonBase& operator=(SingletonBase&&) = delete;

protected:
    SingletonBase() = default;
    virtual ~SingletonBase() = default;
};

#endif // SINGLETONBASE_H