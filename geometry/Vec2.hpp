#pragma once
template<typename T>
class Matrix44;

template <typename T>
class Vec2
{
public:
	Vec2()
	: x(0)
	, y(0)
	{
	}

	Vec2(T x)
	: x(x)
	, y(x)
	{
	}
	Vec2(T x, T y)
	: x(x)
	, y(y)
	{
	}
	
	const T operator[](int i) const
	{
		return (&x)[i];
	}

	T& operator[](int i)
	{
		return (&x)[i];
	}

	Vec2 operator + (const Vec2<T> other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator - (const Vec2 other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator * (T k) const
	{
		return Vec2(x * k, y * k);
	}

	T dot(const Vec2 other) const
	{
		return x * other.x + y * other.y;
	}
	
	T length2() const
	{
		return x * x + y * y;
	}

	T length() const
	{
		return sqrt(length2());
	}

	Vec2& normalize()
	{
		T l2 = length2();
		if (l2 > 0)
		{
			T k = 1 / sqrt(l2);
			x *= k;
			y *= k;
		}
		return *this;
	}

private:
	T x,y;
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const Vec2<T>& other)
{
	s << "(" << other[0] << ", " << other[1] << ")";
	return s;
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
