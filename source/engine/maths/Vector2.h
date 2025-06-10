#ifndef VECTOR2_H
#define VECTOR2_H

#pragma once

#include <type_traits>
#include <string>
#include <sstream>

template <typename T>
class Vector2
{
public:
    T x, y;

    Vector2(T x) : Vector2(x, x) { }

    Vector2(T x, T y) : x(x), y(y)
    {
        static_assert(std::is_same<T, int>::value
            || std::is_same<T, float>::value
            || std::is_same<T, double>::value, "Vector2<T>: T must be int, float or double");
    }

    const char* ToString() const
    {
        static std::string result;
        std::ostringstream ss;
        ss << "{" << x << ", " << y << "}";
        result = ss.str();
        return result.c_str();
    }

    template <typename U>
    Vector2<T> operator*(const U& v)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector2<T>: U must be int, float, or double");

        return Vector2<T>(x * v, y * v);
    }

    Vector2<T> operator+(const Vector2<T>& vec)
    {
        return Vector2<T>(x + vec.x, y + vec.y);
    }

    Vector2<T> operator-(const Vector2<T>& vec)
    {
        return Vector2<T>(x - vec.x, y - vec.y);
    }

    template <typename U>
    Vector2<T> operator+(const U& v)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector2<T>: U must be int, float, or double");

        return Vector2<T>(x + v, y + v);
    }

    template <typename U>
    Vector2<T> operator-(const U& v)
    {
        return *this + (v * (U)-1);
    }

    Vector2<T>& operator=(const Vector2<T>& vec)
    {
        if (this != &vec)
        {
            x = vec.x;
            y = vec.y;
        }
        return *this;
    }

    Vector2<T>& operator+=(const Vector2<T>& vec)
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    Vector2<T>& operator-=(const Vector2<T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }
#pragma region STATICS
    static const Vector2<T> Zero;
    static const Vector2<T> One;
#pragma endregion
};

// Static member definitions
template<typename T>
const Vector2<T> Vector2<T>::Zero = Vector2<T>(0);

template<typename T>
const Vector2<T> Vector2<T>::One = Vector2<T>(1);

#endif