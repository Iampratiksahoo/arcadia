#ifndef VECTOR4_H
#define VECTOR4_H
#pragma once

#include <type_traits>
#include <string>
#include <sstream>

template <typename T>
class Vector4
{
public:
    T x, y, z, w;

    Vector4(T x) : Vector4(x, x, x, x) {}

    Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
    {
        static_assert(std::is_same<T, int>::value
            || std::is_same<T, float>::value
            || std::is_same<T, double>::value, "Vector4<T>: T must be int, float or double");
    }

    const char* ToString() const
    {
        static std::string result;
        std::ostringstream ss;
        ss << "{" << x << ", " << y << ", " << z << ", " << w << "}";
        result = ss.str();
        return result.c_str();
    }

    template <typename U>
    Vector4<T> operator*(const U& v)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector4<T>: U must be int, float, or double");

        return Vector4<T>(x * v, y * v, z * v, w * v);
    }

    Vector4<T> operator+(const Vector4<T>& vec)
    {
        return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }

    Vector4<T> operator-(const Vector4<T>& vec)
    {
        return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }

    template <typename U>
    Vector4<T> operator+(const U& v)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector4<T>: U must be int, float, or double");

        return Vector4<T>(x + v, y + v, z + v, w + v);
    }

    template <typename U>
    Vector4<T> operator-(const U& v)
    {
        return *this + (v * (U)-1);
    }

    Vector4<T>& operator=(const Vector4<T>& vec)
    {
        if (this != &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
            w = vec.w;
        }
        return *this;
    }

    Vector4<T>& operator+=(const Vector4<T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        w += vec.w;
        return *this;
    }

    Vector4<T>& operator-=(const Vector4<T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        w -= vec.w;
        return *this;
    }
#pragma region STATICS
    static const Vector4<T> Zero;
    static const Vector4<T> One;
#pragma endregion
};

// Static member definitions
template<typename T>
const Vector4<T> Vector4<T>::Zero = Vector4<T>(0);

template<typename T>
const Vector4<T> Vector4<T>::One = Vector4<T>(1);

#endif