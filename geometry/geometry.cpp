// geometry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix44.hpp"
#include "Vec3.hpp"
#include "Utils.h"
#include "interpolation.hpp"

void TestLinear()
{
	srand(777);
	const int cell_size = 11;
	const int colors_size = 20;

	Vec3f grid1d[colors_size];
	Vec3f* p_c = &grid1d[0];
	for (int i = 0; i < colors_size; ++i)
	{
		for (int c = 0; c < 3; ++c)
			(*p_c)[c] = rand() / (float)RAND_MAX;
		++p_c;
	}

	int image_width = cell_size * colors_size;
	Vec3f* p_image = new Vec3f[image_width * cell_size];
	Vec3f* p_px = p_image;
	for (int h = 0; h < cell_size; ++h)
	{
		for (int w = 0; w < image_width; ++w)
		{
			int index = w / cell_size;
			*p_px++ = grid1d[index];
		}
	}
	saveToPPM("./flat.ppm", p_image, image_width, cell_size);

	p_px = p_image;
	for (int h = 0; h < cell_size; ++h)
	{
		for (int w = 0; w < image_width; ++w)
		{
			float gx = (float)(w - cell_size/2) / cell_size;
			int index = (int)gx;
			float tx = std::max<float>(0, gx - index);
			int next_index = std::min(index + 1, colors_size - 1);
			//if (next_index == colors_size-1)
			//	tx = 0;
			*p_px++ = linear<Vec3f>(tx, grid1d[index], grid1d[next_index]);
		}
	}
	saveToPPM("./linear.ppm", p_image, image_width, cell_size);

	delete[] p_image;
}

void TestBilinear()
{
	srand(777);
	const int cell_size = 11;
	const int colors_size = 20;

	Vec3f grid2d[colors_size* colors_size];
	Vec3f* p_c = &grid2d[0];
	for (int h = 0; h < colors_size; ++h)
	{
		for (int w = 0; w < colors_size; ++w)
		{
			for (int c = 0; c < 3; ++c)
				(*p_c)[c] = rand() / (float)RAND_MAX;
			++p_c;
		}
	}

	int image_size = cell_size * colors_size;
	Vec3f* p_image = new Vec3f[image_size * image_size];
	Vec3f* p_px = p_image;
	for (int h = 0; h < image_size; ++h)
	{
		int ver_index = h / cell_size;
		for (int w = 0; w < image_size; ++w)
		{
			int hor_index = w / cell_size;
			*p_px++ = grid2d[ver_index* colors_size + hor_index];
		}
	}
	saveToPPM("./flat2.ppm", p_image, image_size, image_size);

	p_px = p_image;
	for (int h = 0; h < image_size; ++h)
	{
		float gy = (float)(h - cell_size / 2) / cell_size;
		int index_y = (int)gy;
		float ty = std::max<float>(0, gy - index_y);
		int next_index_y = std::min(index_y + 1, colors_size - 1);
		for (int w = 0; w < image_size; ++w)
		{
			float gx = (float)(w - cell_size / 2) / cell_size;
			int index_x = (int)gx;
			float tx = std::max<float>(0, gx - index_x);
			int next_index_x = std::min(index_x + 1, colors_size - 1);
			//if (next_index == colors_size-1)
			//	tx = 0;
			int c00 = index_y * colors_size + index_x;
			int c01 = index_y * colors_size + next_index_x;
			int c10 = next_index_y * colors_size + index_x;
			int c11 = next_index_y * colors_size + next_index_x;
			*p_px++ = bilinear<Vec3f>(tx, ty, grid2d[c00], grid2d[c01], grid2d[c10], grid2d[c11]);
		}
	}
	saveToPPM("./bilinear.ppm", p_image, image_size, image_size);

	delete[] p_image;
}

void TestVec3()
{
	Vec3f v;
	Vec3f v1(2);
	Vec3f v2(1, 2, 3);
	v1[2] = 3;
	float dot = v2.dot(v1);
	std::cout << dot << std::endl;
	Vec3f a(2, 3, 2);
	Vec3f b(-1, 2, -2);
	Vec3f c = a.cross(b);
	Vec3f c2 = b.cross(a);
	c.normalize();
	c2.normalize();
	std::cout << c << std::endl;
	std::cout << c2 << std::endl;
	std::cout << c + c2 << std::endl;
}

void TestMatrix44()
{
	Matrix44f m;
	std::cout << m << std::endl;
	Matrix44<double> d(0.707107, 0, -0.707107, 0, -0.331295, 0.883452, -0.331295, 0, 0.624695, 0.468521, 0.624695, 0, 4.000574, 3.00043, 4.000574, 1);
	std::cout << d << std::endl;
	Matrix44<double> dinv = d.inverse();
	std::cout << dinv << std::endl;
	std::cout << d * dinv << std::endl;

	std::cout << d.det() << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	//	Matrix44f d2(0,1,2,3,4,5,6,7,2,2,1,1,4,-3,2,1);
	Matrix44f d2(1.2f, 4.3f, 8.1f, 0, 0, 0, 9.1f, 0, 0, -5.4f, 0.3f, 0, 0, 0.3f, 0.8f, 1);
	std::cout << d2 << std::endl;
	std::cout << "det = " << d2.det() << std::endl;
	std::cout << "inverse" << std::endl;
	Matrix44f d2inv = d2.inverse();
	std::cout << d2inv << std::endl;
	std::cout << "check" << std::endl;
	std::cout << d2 * d2inv << std::endl;

	Vec3<double> p1(0, 1, 2);
	Vec3<double> p2 = d * p1;
	Vec3<double> p3 = dinv * p2;
	std::cout << "point " << p1 << " -> " << p2 << " -> " << p3 << std::endl;

	p2 = p1 * d;
	p3 = p2 * dinv;
	std::cout << "point " << p1 << " -> " << p2 << " -> " << p3 << std::endl;
}
void TestLookAt()
{
	Vec3f camera_pos(0,3,3);
	Vec3f object_pos(0,0,0);
	Matrix44f res = lookAt(camera_pos, object_pos);
	std::cout << "matrix " << res << std::endl;
	Vec3f test_poss[] = { Vec3f(-2,-1,1),Vec3f(-2,-1,-1),Vec3f(-2,1,-1),Vec3f(-2,1,1), Vec3f(2,-1,1),Vec3f(2,-1,-1),Vec3f(2,1,-1),Vec3f(2,1,1) };
	for (Vec3f p : test_poss)
	{
		Vec3f res_pos = p * res;
		std::cout << "point " << p << " -> " << res_pos << std::endl;
	}
}
void drawTree();

int main()
{
//	TestVec3();
//	TestMatrix44();
//	TestLinear();
//	TestBilinear();
	drawTree();
	//TestLookAt();
}
