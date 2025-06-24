#ifndef VECTOR3_H
#define VECTOR3_H
#pragma once

#include <type_traits>
#include <string>
#include <sstream>
#include "Math.h"

template <typename T>
class Vector3
{
public:
    T x, y, z;

    Vector3() : Vector3(Vector3<T>::Zero) {}

    Vector3(T x) : Vector3(x, x, x) {}

    Vector3(const Vector3<T>& other) : Vector3(other.x, other.y, other.z) { }

    Vector3(T x, T y, T z) : x(x), y(y), z(z)
    {
        static_assert(std::is_same<T, int>::value
            || std::is_same<T, float>::value
            || std::is_same<T, double>::value, "Vector3<T>: T must be int, float or double");
    }

    const char* ToString() const
    {
        static std::string result;
        std::ostringstream ss;
        ss << "{" << x << ", " << y << ", " << z << "}";
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
        return x*x + y*y + z*z;
    }

    /// @brief Normalizes this Vector
    void Normalize() 
    {
        *this = GetNormalized();
    }

    /// @brief Returns the Normalized version of this Vector 
    Vector3<T> GetNormalized() const
    {
        // initialize it to zero first
        Vector3<T> normalized = Vector3<T>::Zero; 

        // get the magnitude
        float magnitude = Magnitude(); 

        // handle division by zero 
        if( magnitude != 0)
        {
            normalized = Vector3<T>( x/magnitude, y/magnitude, z/magnitude );
        }

        // return to caller 
        return normalized;
    }


    template <typename U>
    Vector3<T> operator*(const U& s)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector3<T>: U must be int, float, or double");

        return Vector3<T>(x * s, y * s, z * s);
    }

    template <typename U> 
    Vector3<T> operator/(const U& s)
    {
        return *this * (1 / s);
    }

    Vector3<T> operator+(const Vector3<T>& vec)
    {
        return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
    }

    Vector3<T> operator-(const Vector3<T>& vec)
    {
        return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
    }

    Vector3<T>& operator=(const Vector3<T>& vec)
    {
        if (this != &vec)
        {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }
        return *this;
    }

    template <typename U>
    Vector3<T> operator+(const U& v)
    {
        static_assert(std::is_same<U, int>::value
            || std::is_same<U, float>::value
            || std::is_same<U, double>::value, "Vector3<T>: U must be int, float, or double");
        return Vector3<T>(x + v, y + v, z + v);
    }

    template <typename U>
    Vector3<T> operator-(const U& v)
    {
        return *this + (v * (U)-1);
    }

    Vector3<T> operator*( const Vector3<T>& vec ) {
        return Vector3<T>(
            x * vec.x,
            y * vec.y,
            z * vec.z
        );
    }

    Vector3<T> operator/( const Vector3<T>& vector ) {
        return Vector3<T>(
            x / vector.x,
            y / vector.y,
            z / vector.z
        );
    }

    Vector3<T>& operator+=(const Vector3<T>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
        return *this;
    }

    Vector3<T>& operator-=(const Vector3<T>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
        return *this;
    }

    bool operator==(const Vector3<T>& vec) const
    {
        return x == vec.x
                && y == vec.y
                && z == vec.z;
    }

    bool operator!=(const Vector3<T>& vec) const
    {
        return !(*this == vec);
    }

    Vector3<T> operator-() const
    {
        return Vector3<T>(-x, -y, -z);
    }

    static Vector3<T> Clamp(const Vector3<T>& value, const Vector3<T>& min, const Vector3<T>& max)
    {
        return Vector3<T>(
            Math::Clamp(value.x, min.x, max.x),
            Math::Clamp(value.y, min.y, max.y),
            Math::Clamp(value.z, min.z, max.z)
        );
    }
#pragma region STATICS
    static const Vector3<T> Zero;
    static const Vector3<T> One;
    static const Vector3<T> Up;
    static const Vector3<T> Down;
    static const Vector3<T> Left;
    static const Vector3<T> Right;
    static const Vector3<T> Forward;
    static const Vector3<T> Backward;
#pragma endregion
};

// Static member definitions
template<typename T>
const Vector3<T> Vector3<T>::Zero = Vector3<T>(0);

template<typename T>
const Vector3<T> Vector3<T>::One = Vector3<T>(1);

template<typename T>
const Vector3<T> Vector3<T>::Up = Vector3<T>(0, 1, 0);

template<typename T>
const Vector3<T> Vector3<T>::Down = Vector3<T>(0, -1, 0);

template<typename T>
const Vector3<T> Vector3<T>::Left = Vector3<T>(-1, 0, 0);

template<typename T>
const Vector3<T> Vector3<T>::Right = Vector3<T>(1, 0, 0);

template<typename T>
const Vector3<T> Vector3<T>::Forward = Vector3<T>(0, 0, 1);

template<typename T>
const Vector3<T> Vector3<T>::Backward = Vector3<T>(0, 0, -1);

#endif