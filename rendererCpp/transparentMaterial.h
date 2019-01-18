#pragma once
#include "material.h"
class transparentMaterial :
	public material
{
public:
	transparentMaterial();
	transparentMaterial(float const &indexOfRefraction);

	vector3 shade(rayHitInfo & info);

protected:
	float indexOfRefraction;
};

