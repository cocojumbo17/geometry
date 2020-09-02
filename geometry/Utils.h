#pragma once
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Matrix44.hpp"

void saveToPPM(const char* file_name, Vec3f* p_data, int width, int height);
Matrix44f lookAt(Vec3f from, Vec3f to, Vec3f up = Vec3f(0, 1, 0));
void computePixelCoordinates(
	const Vec3f pWorld,
	Vec2i& pRaster,
	const Matrix44f& worldToCamera,
	const float& canvasWidth,
	const float& canvasHeight,
	const uint32_t& imageWidth,
	const uint32_t& imageHeight
);
