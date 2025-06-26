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

    static float Min( float value1, float value2 )
    {
        return std::min( value1, value2 );
    }

    static float Max( float value1, float value2 )
    {
        return std::max( value1, value2 );
    }
};

#endif