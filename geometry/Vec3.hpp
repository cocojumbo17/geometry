#pragma once
template<typename T>
class Matrix44;

template <typename T>
class Vec3
{
public:
	Vec3()
	: x(0)
	, y(0)
	, z(0)
	{
	}

	Vec3(T x)
	: x(x)
	, y(x)
	, z(x)
	{
	}
	Vec3(T x, T y, T z)
	: x(x)
	, y(y)
	, z(z)
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

	Vec3 operator + (const Vec3<T> other) const
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	Vec3 operator - (const Vec3 other) const
	{
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 operator * (T k) const
	{
		return Vec3(x * k, y * k, z * k);
	}

	T dot(const Vec3 other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
	
	Vec3 cross(const Vec3<T> other) const
	{
		Vec3 res;
		res[0] = y * other.z - z * other.y;
		res[1] = z * other.x - x * other.z;
		res[2] = x * other.y - y * other.x;
		return res;
	}

	T length2() const
	{
		return x * x + y * y + z * z;
	}

	T length() const
	{
		return sqrt(length2());
	}

	Vec3& normalize()
	{
		T l2 = length2();
		if (l2 > 0)
		{
			T k = 1 / sqrt(l2);
			x *= k;
			y *= k;
			z *= k;
		}
		return *this;
	}

	Vec3 operator *(Matrix44<T> m) const
	{
		T src[] = { x,y,z,1 };
		T dst[] = { 0,0,0,0 };
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				dst[row] += src[col] * m[col][row];
		Vec3<T> res(dst[0], dst[1], dst[2]);
		res = res * (1 / dst[3]);
		return res;
	}

private:
	T x,y,z;
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const Vec3<T>& other)
{
	s << "(" << other[0] << ", " << other[1] << ", " << other[2] << ")";
	return s;
}

typedef Vec3<float> Vec3f;
