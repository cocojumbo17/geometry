#include <fstream>
#include <iostream>
#include <utility>
#include "Utils.h"

void saveToPPM(const char* file_name, Vec3f* p_data, int width, int height)
{
	std::ofstream ofs;
	ofs.open(file_name, std::ios::binary|std::ios::out);
	if (ofs.fail())
	{
		std::cerr << "Cannot open file " << file_name << std::endl;
		return;
	}
	ofs << "P6\n";
	ofs << width << " " << height << "\n255\n";
	Vec3f* p_color = p_data;
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			for (int c = 0; c < 3; ++c)
			{
				ofs << (char)(int)std::fmin(255.0, (*p_color)[c] * 255.0);
			}
			++p_color;
		}
	}
	ofs.close();
}
