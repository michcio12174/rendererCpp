#pragma once
#include "material.h"

class specularMaterial :
	public virtual material
{
public:
	specularMaterial();
	specularMaterial(texture *materialTexture, float const &highlightIntensity, float const &highlightSize);

	vector3 shade(rayHitInfo &info);
private:
	float highlightSize;
	float highlightIntensity;
};

