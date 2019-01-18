#pragma once

class texture
{
public:
	texture();
	texture(float R, float G, float B);
	//loads .bmp image using CImg
	texture(string imagePath, bool repeat);

	virtual vector3 getColor(vector3 const &localHitPoint) const;
	virtual vector3 getColor(float s, float t) const;

protected:
	CImg<unsigned char> *image;
	vector3 defaultColor;
	int width, height;
	bool repeat;
};

