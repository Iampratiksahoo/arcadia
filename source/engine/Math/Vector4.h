#ifndef VECTOR4_H
#define VECTOR4_H
#pragma once

#include <type_traits>
#include <string>
#include <sstream>
#include "Math.h"

template <typename T>
class Vector4
{
public:
    T x, y, z, w;

    Vector4() : Vector4(Vector4<T>::Zero) {}

    Vector4(T x) : Vector4(x, x, x, x) {}

    Vector4(const Vector4<T>& other) : Vector4(other.x, other.y, other.z, other.w) { }

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

    /// @brief Returns the Magnitude/Length of the vector 
    float Magnitude() const
    {
        return std::sqrt( SquareMagnitude() );
    }

    /// @brief Returns the Square Magnitude of the vector 
    float SquareMagnitude() const 
    {
        return x*x + y*y + z*z + w*w;
    }

    /// @brief Normalizes this Vector
    void Normalize() 
    {
        *this = GetNormalized();
    }

    /// @brief Returns the Normalized version of this Vector 
    Vector4<T> GetNormalized() const
    {
        // initialize it to zero first
        Vector4<T> normalized = Vector4<T>::Zero; 

        // get the magnitude
        float magnitude = Magnitude(); 

        // handle division by zero 
        if( magnitude != 0)
        {
            normalized = Vector4<T>( x/magnitude, y/magnitude, z/magnitude, w/magnitude );
        }

        // return to caller 
        return normalized;
    }

    float Dot(const Vector4<float>& other) const
    {
        return x * other.x 
             + y * other.y 
             + z * other.z
             + w * other.w;
    }

    Vector4<T> operator*(const float& s)
    {
        return Vector4<T>(x * s, y * s, z * s, w * s);
    }
 
    Vector4<T> operator/(const float& s)
    {
        if (s == 0.0f)
            throw std::runtime_error("Division by zero in Vector4");

        return *this * (1 / s);
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

    Vector4<T> operator*( const Vector4<T>& vec ) {
        return Vector4<T>(
            x * vec.x,
            y * vec.y,
            z * vec.z,
            w * vec.w
        );
    }

    Vector4<T> operator/( const Vector4<T>& vec ) {
        return Vector4<T>(
            x / vec.x,
            y / vec.y,
            z / vec.z,
            w / vec.w
        );
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

    bool operator==(const Vector4<T>& vec) const
    {
        return x == vec.x
                && y == vec.y
                && z == vec.z 
                && w == vec.w;
    }

    bool operator!=(const Vector4<T>& vec) const
    {
        return !(*this == vec);
    }

    Vector4<T> operator-() const
    {
        return Vector4<T>(-x, -y, -z, -w);
    }

    static Vector4<T> Clamp(const Vector4<T>& value, const Vector4<T>& min, const Vector4<T>& max)
    {
        return Vector4<T>(
            Math::Clamp(value.x, min.x, max.x),
            Math::Clamp(value.y, min.y, max.y),
            Math::Clamp(value.z, min.z, max.z),
            Math::Clamp(value.w, min.w, max.w)
        );
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