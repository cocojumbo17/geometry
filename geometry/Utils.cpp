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

Matrix44f lookAt(Vec3f from, Vec3f to, Vec3f up /*= Vec3f(0, 1, 0)*/)
{
	Vec3f forward = (from - to).normalize();
	Vec3f right = up.cross(forward).normalize();
	Vec3f real_up = forward.cross(right);
	Matrix44f res(right, real_up, forward, from);
	return res;
}

void computePixelCoordinates(
	const Vec3f pWorld,
	Vec2i& pRaster,
	const Matrix44f& worldToCamera,
	const float& canvasWidth,
	const float& canvasHeight,
	const uint32_t& imageWidth,
	const uint32_t& imageHeight
)
{
	Vec3f pCamera = pWorld * worldToCamera;
	Vec2f pScreen;
	pScreen[0] = pCamera[0] / -pCamera[2];
	pScreen[1] = pCamera[1] / -pCamera[2];
	Vec2f pNDC;
	pNDC[0] = (pScreen[0] + canvasWidth * 0.5) / canvasWidth;
	pNDC[1] = (pScreen[1] + canvasHeight * 0.5) / canvasHeight;
	pRaster[0] = (int)(pNDC[0] * imageWidth);
	pRaster[1] = (int)((1 - pNDC[1]) * imageHeight);
}
