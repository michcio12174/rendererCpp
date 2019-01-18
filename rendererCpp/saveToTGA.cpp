#include "stdafx.h"
#include "saveToTGA.h"

bool saveToTGA::saveImage(int width, int height, vector4 *buffer)
{
	int length = width * height;
	int *intBuffer = new int[length];
	for (int i = 0; i < length; ++i) intBuffer[i] = buffer[i].toInt();

	return saveToFile(width, height, intBuffer, "TGAfromVector4");
}

bool saveToTGA::saveImage(int width, int height, vector3 * buffer)
{
	int length = width * height;
	int *intBuffer = new int[length];
	for (int i = 0; i < length; ++i) intBuffer[i] = buffer[i].toInt();

	bool result = saveToFile(width, height, intBuffer, "TGAfromVector3");
	delete intBuffer;
	return result;
}

bool saveToTGA::saveToFile(int width, int height, int* buffer, string name)
{
	string path = "../images/" + name + ".tga";

	unsigned short header[9] = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		width, height,
		0x0820 };

	FILE *f = fopen(path.c_str(), "wb+");
	if (NULL == f) return false;
	else {
		fwrite(header, 2, 9, f);
		fwrite(buffer, 4, width*height, f);
		fclose(f);
		return true;
	}
}
