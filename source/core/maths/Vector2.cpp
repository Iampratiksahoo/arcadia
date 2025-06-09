#include "Vector2.h"

#include <iostream>
#include <type_traits>

template<typename T>
const char* Vector2<T>::ToString() const
{
	return "{" + x + ", " + y + "}";
}

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator*(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector2<T>: T must be int, float, or double");

	return Vector2<T>(x * v, y * v);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec)
{
	return Vector2<T>(x + vec.x, y + vec.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec)
{
	return Vector2<T>(x - vec.x, y - vec.y);
}

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator+(const U& v)
{
	static_assert(std::is_same<U, int>::value
		|| std::is_same<U, float>::value
		|| std::is_same<U, double>::value, "Vector2<T>: T must be int, float, or double");
	return Vector2<T>(x + v, y + v);
}

template<typename T>
template<typename U>
Vector2<T> Vector2<T>::operator-(const U& v)
{
	return *this + (v * (U) - 1);
}