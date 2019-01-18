#include "stdafx.h"
#include "ambientLight.h"


ambientLight::ambientLight():
	intensity(0.1f),
	color(vector3(1, 1, 1))
{
}

ambientLight::ambientLight(vector3 color, float intensity):
	intensity(intensity),
	color(color)
{
}

vector3 ambientLight::getLight()
{
	return color*intensity;
}

void ambientLight::operator=(ambientLight const & otherLight)
{
	intensity = otherLight.intensity;
	color = otherLight.color;
}
