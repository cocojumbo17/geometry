// geometry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Matrix44.hpp"
#include "Vec3.hpp"
int main()
{
    std::cout << "Hello World!\n";
    Vec3f v;
	Vec3f v1(2);
	Vec3f v2(1,2,3);
	v1[2] = 3;
	float dot = v2.dot(v1);
	std::cout << dot << std::endl;
	Vec3f a(2,3,2);
	Vec3f b(-1, 2, -2);
	Vec3f c = a.cross(b);
	Vec3f c2 = b.cross(a);
	c.normalize();
	c2.normalize();
	std::cout << c << std::endl;
	std::cout << c2 << std::endl;
	std::cout << c+c2 << std::endl;

	Matrix44f m;
	std::cout << m << std::endl;
	Matrix44<double> d(0.707107, 0, -0.707107, 0, -0.331295, 0.883452, -0.331295, 0, 0.624695, 0.468521, 0.624695, 0, 4.000574, 3.00043, 4.000574, 1);
	std::cout << d << std::endl;
	Matrix44<double> dinv = d.inverse();
	std::cout << dinv << std::endl;
	std::cout << d*dinv << std::endl;

	std::cout << d.det() << std::endl;

	std::cout << "-----------------------------------------" << std::endl;
	Matrix44f d2(0,1,2,3,4,5,6,7,2,2,1,1,4,-3,2,1);
	std::cout << d2 << std::endl;
	std::cout << "det = " << d2.det() << std::endl;
	std::cout << "inverse" << std::endl;
	Matrix44f d2inv = d2.inverse();
	std::cout << d2inv << std::endl;
	std::cout << "check" << std::endl;
	std::cout << d2*d2inv << std::endl;

	Vec3<double> p1(0, 1, 2);
	Vec3<double> p2 = d * p1;
	Vec3<double> p3 = dinv * p2;
	std::cout << "point " << p1 << " -> " << p2 << " -> " << p3 << std::endl;

	p2 = p1*d;
	p3 = p2 * dinv;
	std::cout << "point " << p1 << " -> " << p2 << " -> " << p3 << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
