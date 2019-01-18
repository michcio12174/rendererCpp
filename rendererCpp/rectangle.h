#pragma once
#include "plane.h"
class rectangle :
	public plane
{
public:
	rectangle(vector3 leftUpperCorner, float width, float height, material *materialToUse);

	bool hit(rayHitInfo &info);

private:
	float width, height;
};

