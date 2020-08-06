#pragma once
#include <iomanip>

template<typename T>
class Vec3;

template<typename T>
class Matrix44
{
public:
	Matrix44() {};
	Matrix44(T a00, T a01, T a02, T a03,
			T a10, T a11, T a12, T a13, 
			T a20, T a21, T a22, T a23, 
			T a30, T a31, T a32, T a33) {
		m_m[0][0] = a00;
		m_m[0][1] = a01;
		m_m[0][2] = a02;
		m_m[0][3] = a03;
		m_m[1][0] = a10;
		m_m[1][1] = a11;
		m_m[1][2] = a12;
		m_m[1][3] = a13;
		m_m[2][0] = a20;
		m_m[2][1] = a21;
		m_m[2][2] = a22;
		m_m[2][3] = a23;
		m_m[3][0] = a30;
		m_m[3][1] = a31;
		m_m[3][2] = a32;
		m_m[3][3] = a33;
	}
	const T* operator[](int i) const
	{
		return m_m[i];
	}

	T* operator[](int i)
	{
		return m_m[i];
	}

	Matrix44 transpose() const
	{
		Matrix44 res;
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				res[row][col] = m_m[col][row];
		return res;
	}

	Matrix44 operator * (T k) const
	{
		Matrix44 temp = *this;
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				temp[row][col] *= k;
		return temp;
	}

	Matrix44 operator * (Matrix44 other) const
	{
		Matrix44 res;
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				res[row][col] = m_m[row][0] * other[0][col] + m_m[row][1] * other[1][col] +
								m_m[row][2] * other[2][col] + m_m[row][3] * other[3][col];
		return res;
	}

	T det() const 
	{
		Matrix44 temp = *this;
		int non_zero_row = temp.findNonZeroRow();
		if (non_zero_row == -1)
			return 0;//column with all 0
		if (non_zero_row != 0)
			temp.switchRows(0, non_zero_row);
		temp.makeFirstZero();
		return temp.det3(0,0)*temp[0][0];
	}

	Matrix44 inverse() const
	{
		Matrix44 res = *this;
		T d = res.det();
		if (d == 0)
			return res;
		d = 1 / d;
		res = res.transpose();
		res = complement(res);
		res = res * d;
		return res;
	}

	Vec3<T> operator *(Vec3<T> v) const 
	{
		T src[] = { v[0],v[1],v[2],1 };
		T dst[] = { 0,0,0,0 };
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
				dst[row] += m_m[row][col] * src[col];
		Vec3<T> res(dst[0], dst[1], dst[2]);
		res = res * (1 / dst[3]);
		return res;
	}
protected:
	int findNonZeroRow() const
	{
		int nonZeroRow = -1;
		for (int i = 0; i < 4; ++i)
		{
			if (m_m[i][0] != 0)
			{
				nonZeroRow = i;
				break;
			}
		}
		return nonZeroRow;
	}
	void switchRows(int row1, int row2)
	{
		for (int i = 0; i < 4; ++i)
		{
			T temp = m_m[row1][i];
			m_m[row1][i] = m_m[row2][i];
			m_m[row2][i] = -temp;//change sign
		}
	}
	void makeFirstZero()
	{
		for (int row = 1; row < 4; ++row)
		{
			T k = m_m[row][0] / m_m[0][0];
			for (int col = 0; col < 4; ++col)
				m_m[row][col] -= m_m[0][col]*k;
		}
	}
	void minorIndexes(int without_row, int without_col, int columns[3], int rows[3]) const
	{
		int* p_col = &columns[0];
		int* p_row = &rows[0];
		for (int i = 0; i < 4; ++i)
		{
			if (i != without_row)
				*p_row++ = i;
			if (i != without_col)
				*p_col++ = i;
		}
	}
	T det3(int without_row, int without_col) const
	{
		int columns[3];
		int rows[3];
		minorIndexes(without_row, without_col, columns, rows);
		return	m_m[rows[0]][columns[0]] * m_m[rows[1]][columns[1]] * m_m[rows[2]][columns[2]] +
				m_m[rows[0]][columns[1]] * m_m[rows[1]][columns[2]] * m_m[rows[2]][columns[0]] +
				m_m[rows[0]][columns[2]] * m_m[rows[1]][columns[0]] * m_m[rows[2]][columns[1]] -
				m_m[rows[0]][columns[2]] * m_m[rows[1]][columns[1]] * m_m[rows[2]][columns[0]] -
				m_m[rows[2]][columns[2]] * m_m[rows[0]][columns[1]] * m_m[rows[1]][columns[0]] -
				m_m[rows[0]][columns[0]] * m_m[rows[2]][columns[1]] * m_m[rows[1]][columns[2]];
	}

	Matrix44 complement(const Matrix44& m) const
	{
		Matrix44 res;
		for (int row = 0; row < 4; ++row)
			for (int col = 0; col < 4; ++col)
			{
				res[row][col] = m.complement3(row, col);
			}
		return res;
	}

	T complement3(int without_row, int without_col) const
	{
		T sign = ((without_row + without_col) % 2 == 0) ? (T)1 : (T)-1;
		return sign * det3(without_row, without_col);
	}

private:
	T m_m[4][4]={ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
};

template<typename T>
std::ostream& operator << (std::ostream& s, const Matrix44<T>& m)
{
	const int w = 12;
	auto old_flags = s.flags(std::ios_base::fixed);
	auto old_precision = s.precision(5);
	s << "(" << std::setw(w) << m[0][0] << " " << std::setw(w) << m[0][1] << " " << std::setw(w) << m[0][2] << " " << std::setw(w) << m[0][3] << std::endl;
	s << " " << std::setw(w) << m[1][0] << " " << std::setw(w) << m[1][1] << " " << std::setw(w) << m[1][2] << " " << std::setw(w) << m[1][3] << std::endl;
	s << " " << std::setw(w) << m[2][0] << " " << std::setw(w) << m[2][1] << " " << std::setw(w) << m[2][2] << " " << std::setw(w) << m[2][3] << std::endl;
	s << " " << std::setw(w) << m[3][0] << " " << std::setw(w) << m[3][1] << " " << std::setw(w) << m[3][2] << " " << std::setw(w) << m[3][3] << ")" << std::endl;
	s.flags(old_flags);
	s.precision(old_precision);
	return s;
}

typedef Matrix44<float> Matrix44f;