#ifndef MATH_H
#define MATH_H

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
};

#endif