#pragma once
#include "material.h"

class diffuseMaterial : virtual public material
{
public:
	diffuseMaterial(texture *materialTexture, float const &diffuseCoefficient);

	vector3 shade(rayHitInfo &info);
private:
	float diffuseCoefficient;
};

