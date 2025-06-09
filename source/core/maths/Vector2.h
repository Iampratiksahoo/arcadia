#include <type_traits>

template <typename T>  
class Vector2
{
public: 
    Vector2(T x) : Vector2(x, x) { }

	Vector2(T x, T y) : x(x), y(y)
	{
		static_assert(std::is_same<T, int>::value
			|| std::is_same<T, float>::value
			|| std::is_same<T, double>::value, "Vector2<T>: T must be int, float or double");
	}

	const char* ToString() const;

	template <typename U>
	Vector2<T> operator*(const U& v);

	Vector2<T> operator+(const Vector2<T>& vec);
	Vector2<T> operator-(const Vector2<T>& vec);

	template <typename U>
	Vector2<T> operator+(const U& v);

	template <typename U>
	Vector2<T> operator-(const U& v);

public:
	T x;
	T y;
};