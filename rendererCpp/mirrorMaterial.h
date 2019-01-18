#pragma once
#include "material.h"
class mirrorMaterial :
	public material
{
public:
	mirrorMaterial();

	vector3 shade(rayHitInfo &info);
};

