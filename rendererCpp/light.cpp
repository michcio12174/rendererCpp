#include "stdafx.h"
#include "light.h"

light::light(vector3 color, vector3 direction):
	color(color),
	intensity(1),
	origin(direction),
	isPointLight(false)
{
	origin.normalize();
}

light::light(vector3 color, float intensity, vector3 origin):
	color(color),
	intensity(intensity),
	origin(origin),
	isPointLight(true)
{
	color.scaleToOne();
}

vector3 light::getLight(vector3 position)
{
	if (isPointLight) return color * (intensity / (1 + position.distanceSquare(origin)));
	else return color;
}

vector3 light::getVectorToLight(vector3 position) //return normalized vector
{
	if(isPointLight) return (origin - position).normalize();
	else return -origin;
}
