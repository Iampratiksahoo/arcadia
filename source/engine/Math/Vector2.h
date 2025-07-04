#ifndef VECTOR2_H
#define VECTOR2_H

#pragma once

#include <type_traits>
#include <string>
#include <sstream>
#include "Math.h"

template <typename T>
class Vector2
{
public:
    T x, y;

    Vector2() : Vector2(Vector2<T>::Zero) {}

    Vector2(T x) : Vector2(x, x) { }

    Vector2(const Vector2<T>& other) : Vector2(other.x, other.y) { }

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
        return std::sqrt( SquareMagnitude() );
    }

    /// @brief Returns the Square Magnitude of the vector 
    float SquareMagnitude() const 
    {
        return x*x + y*y;
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

    float Dot(const Vector2<T>& other) const
    {
        return x * other.x 
             + y * other.y;
    }

    Vector2<T> operator*(const float& s) const
    {
        return Vector2<T>(x * s, y * s);
    }
 
    Vector2<T> operator/(const float& s) const
    {
        if (s == 0.0f)
            throw std::runtime_error("Division by zero in Vector2");

        return *this * (1 / s);
    }

    Vector2<T> operator+(const Vector2<T>& vec) const
    {
        return Vector2<T>(x + vec.x, y + vec.y);
    }

    Vector2<T> operator-(const Vector2<T>& vec) const
    {
        return Vector2<T>(x - vec.x, y - vec.y);
    }

    Vector2<T> operator*( const Vector2<T>& vec ) const {
        return Vector2<T>(
            x * vec.x,
            y * vec.y
        );
    }

    Vector2<T> operator/( const Vector2<T>& vector ) const {
        return Vector2<T>(
            x / vector.x,
            y / vector.y
        );
    }

    template <typename U>
    Vector2<T> operator+(const U& v) const
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector2<T>: U must be int, float, or double");

        return Vector2<T>(x + v, y + v);
    }

    template <typename U>
    Vector2<T> operator-(const U& v) const
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

    Vector2<T> operator-() const
    {
        return Vector2<T>(-x, -y);
    }

    static Vector2<T> Clamp(const Vector2<T>& value, const Vector2<T>& min, const Vector2<T>& max)
    {
        return Vector2<T>(
            Math::Clamp(value.x, min.x, max.x),
            Math::Clamp(value.y, min.y, max.y)
        );
    }
#pragma region STATICS
    static Vector2<T> Zero;
    static Vector2<T> One;
    static Vector2<T> Up;
    static Vector2<T> Down;
    static Vector2<T> Left;
    static Vector2<T> Right;
#pragma endregion
};

// Static member definitions
template<typename T>
Vector2<T> Vector2<T>::Zero = Vector2<T>(0);

template<typename T>
Vector2<T> Vector2<T>::One = Vector2<T>(1);

template<typename T>
Vector2<T> Vector2<T>::Up = Vector2<T>(0, 1);

template<typename T>
Vector2<T> Vector2<T>::Down = Vector2<T>(0, -1);

template<typename T>
Vector2<T> Vector2<T>::Left = Vector2<T>(-1, 0);

template<typename T>
Vector2<T> Vector2<T>::Right = Vector2<T>(1, 0);

#endif