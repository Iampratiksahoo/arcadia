#ifndef MATH_H
#define MATH_H

#include <algorithm> 
#include <cmath>      

#define MATH_PI (float) 22 / 7

class Math
{
public:
    static float Clamp(float value, float min, float max) 
    {
        return std::max(min, std::min(max, value));
    }  

    static float Abs(float value)
    {
        return std::abs( value );
    }

    static float Min( float value1, float value2 )
    {
        return std::min( value1, value2 );
    }

    static float Max( float value1, float value2 )
    {
        return std::max( value1, value2 );
    }

    static float DegToRad(float deg)
    {
        return deg * (MATH_PI / 180.f);
    }

    static float RadToDeg(float rad)
    {
        return rad * (180.f / MATH_PI);
    }
};

#endif