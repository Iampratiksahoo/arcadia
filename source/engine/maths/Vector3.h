#include <type_traits>

template <typename T>  
class Vector3
{
public: 
    Vector3(T x) : Vector3(x, x, x){}

	Vector3(T x, T y, T z) : x(x), y(y), z(z)
	{
		static_assert(std::is_same<T, int>::value
			|| std::is_same<T, float>::value
			|| std::is_same<T, double>::value, "Vector3<T>: T must be int, float or double");
	}

	const char* ToString() const;

	template <typename U>
	Vector3<T> operator*(const U& v);

	Vector3<T> operator+(const Vector3<T>& vec);
	Vector3<T> operator-(const Vector3<T>& vec);

	template <typename U>
	Vector3<T> operator+(const U& v);

	template <typename U>
	Vector3<T> operator-(const U& v);

public:
	T x;
	T y;
	T z;
};