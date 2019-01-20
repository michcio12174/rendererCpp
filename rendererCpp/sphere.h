#pragma once
#include "geometricObject.h"

class sphere: public geometricObject
{
public:
	sphere() {}
	sphere(vector3 origin, float radius, material *materialToUse);
	sphere(const sphere &sphere);

	virtual void hit(rayHitInfo &info);
protected:
	vector3 origin;
	float radius;
};

