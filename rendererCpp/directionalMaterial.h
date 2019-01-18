#pragma once
#include "material.h"
class directionalMaterial :
	public material
{
public:
	directionalMaterial();
	directionalMaterial(texture *materialTexture);

	vector3 shade(rayHitInfo &info);
};

