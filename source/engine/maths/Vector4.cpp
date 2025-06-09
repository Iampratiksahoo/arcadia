#include "Vector4.h"

#include <iostream>
#include <type_traits>

template<typename T>
const char* Vector4<T>::ToString() const
{
	return "{" + x + ", " + y + ", " + z + ", " +  w +"}";
}

template<typename T>
template<typename U>
Vector4<T> Vector4<T>::operator*(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector4<T>: U must be int, float, or double");

	return Vector4<T>(x * v, y * v, z * v, w * v);
}

template<typename T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& vec)
{
	return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

template<typename T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& vec)
{
	return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

template<typename T>
template<typename U>
Vector4<T> Vector4<T>::operator+(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector4<T>: U must be int, float, or double");
	return Vector4<T>(x + v, y + v, z + v, w + v);
}

template<typename T>
template<typename U>
Vector4<T> Vector4<T>::operator-(const U& v)
{
	return *this + (v * (U) - 1);
}