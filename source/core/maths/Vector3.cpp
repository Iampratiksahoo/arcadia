#include "Vector3.h"

#include <iostream>
#include <type_traits>

template<typename T>
const char* Vector3<T>::ToString() const
{
	return "{" + x + ", " + y + ", " + z + "}";
}

template<typename T>
template<typename U>
Vector3<T> Vector3<T>::operator*(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector3<T>: U must be int, float, or double");

	return Vector3<T>(x * v, y * v, z * v);
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& vec)
{
	return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& vec)
{
	return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
}

template<typename T>
template<typename U>
Vector3<T> Vector3<T>::operator+(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector3<T>: U must be int, float, or double");
	return Vector3<T>(x + v, y + v, z + v);
}

template<typename T>
template<typename U>
Vector3<T> Vector3<T>::operator-(const U& v)
{
	return *this + (v * (U) - 1);
}