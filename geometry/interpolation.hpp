#pragma once

template <typename T>
T linear(float tx, const T& from, const T& to)
{
	T res = from * (1.0f - tx) + to * tx;
	return res;
}

template <typename T>
T bilinear(float tx, float ty, const T& c00, const T& c01, const T& c10, const T& c11)
{
	T a = c00 * (1.0f - tx) + c01 * tx;
	T b = c10 * (1.0f - tx) + c11 * tx;
	T res = a * (1.0f - ty) + b * ty;
	return res;
}