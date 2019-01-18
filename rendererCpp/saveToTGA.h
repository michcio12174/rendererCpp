#pragma once

#include "vectorsAndMatrices.h"

class saveToTGA
{
public:
	static bool saveImage(int width, int height, vector4 *buffer);
	static bool saveImage(int width, int height, vector3 *buffer);
private:
	static bool saveToFile(int width, int height, int* buffer, string name);
};

