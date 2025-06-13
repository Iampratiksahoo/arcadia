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

    /// @brief Returns the Magnitude/Length of the vector 
    float Magnitude() const
    {
        return std::sqrt( x*x + y*y );
    }

    /// @brief Normalizes this Vector
    void Normalize() 
    {
        *this = GetNormalized();
    }

    /// @brief Returns the Normalized version of this Vector 
    Vector2<T> GetNormalized() const
    {
        // initialize it to zero first
        Vector2<T> normalized = Vector2<T>::Zero; 

        // get the magnitude
        float magnitude = Magnitude(); 

        // handle division by zero 
        if( magnitude != 0)
        {
            normalized = Vector2<T>( x/magnitude, y/magnitude );
        }

        // return to caller 
        return normalized;
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

    bool operator==(const Vector2<T>& vec) const
    {
        return x == vec.x
                && y == vec.y;
    }

    bool operator!=(const Vector2<T>& vec) const
    {
        return !(*this == vec);
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