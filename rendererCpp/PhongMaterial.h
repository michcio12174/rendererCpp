#pragma once
#include "diffuseMaterial.h"
#include "specularMaterial.h"

class PhongMaterial :
	public material
{
public:
	PhongMaterial(texture *materialTexture, float const &highlightSize);
	PhongMaterial(texture *materialTexture, float const &specularCoefficient, float const &highlightSize, float const &diffuseCoefficient);

	vector3 shade(rayHitInfo &info);

private:
	float diffuseCoefficient;
	float highlightSize;
	float highlightIntensity;
};

