#include "stdafx.h"
#include "texture.h"


texture::texture(): 
	width(0), 
	height(0), 
	image(NULL),
	defaultColor(1, 0, 0),
	repeat(false)
{
}

texture::texture(float R, float G, float B):
	width(0),
	height(0),
	image(NULL),
	defaultColor(R, G, B),
	repeat(false)
{
}

texture::texture(string imagePath, bool repeat):
	defaultColor(1, 0, 0),
	repeat(repeat)
{
	image = new CImg<unsigned char>(imagePath.c_str());
	width = image->width();
	height = image->height();
}

vector3 texture::getColor(vector3 const & localHitPoint) const
{
	int u, v;

	if (image) {
		if (repeat) {
			u = (int)(localHitPoint.x - floor(localHitPoint.x)) * width;
			v = (int)(localHitPoint.y - floor(localHitPoint.y)) * height;
		}
		else {
			u = (int)max(0.0f, min(localHitPoint.x * width, width - 1.0f));
			v = (int)max(0.0f, min(localHitPoint.y * height, width - 1.0f));
		}
		//w obrazku mamy kolor w zakresie od 0 do 255, a renderer operuje na kolorach w zakresie od 0 do 1
		//dlatego u¿ywam funkcji scale
		vector3 textureColor = vector3((*image)(u, v, 0), (*image)(u, v, 1), (*image)(u, v, 2));
		textureColor.scaleToOne();
		return textureColor;
	}
	else return defaultColor;
}

vector3 texture::getColor(float s, float t) const
{
	int u, v;

	if (image) {
		if (repeat) {
			u = (int)(s - floor(s)) * width;
			v = (int)(t - floor(t)) * height;
		}
		else {
			u = (int)max(0.0f, min(s * width, width - 1.0f));
			v = (int)max(0.0f, min(t * height, width - 1.0f));
		}
		//w obrazku mamy kolor w zakresie od 0 do 255, a renderer operuje na kolorach w zakresie od 0 do 1
		//dlatego u¿ywam funkcji scale
		vector3 textureColor = vector3((*image)(u, v, 0), (*image)(u, v, 1), (*image)(u, v, 2));
		textureColor.scaleToOne();
		return textureColor;
	}
	else return defaultColor;
}
