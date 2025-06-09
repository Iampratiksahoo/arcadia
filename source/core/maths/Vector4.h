#include <type_traits>

template <typename T>  
class Vector4
{
public: 
    Vector4(T x) : Vector4(x, x, x, x){}

	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w)
	{
		static_assert(std::is_same<T, int>::value
			|| std::is_same<T, float>::value
			|| std::is_same<T, double>::value, "Vector4<T>: T must be int, float or double");
	}

	const char* ToString() const;

	template <typename U>
	Vector4<T> operator*(const U& v);

	Vector4<T> operator+(const Vector4<T>& vec);
	Vector4<T> operator-(const Vector4<T>& vec);

	template <typename U>
	Vector4<T> operator+(const U& v);

	template <typename U>
	Vector4<T> operator-(const U& v);

public:
	T x;
	T y;
	T z;
    T w;
};