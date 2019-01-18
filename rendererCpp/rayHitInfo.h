#pragma once
#include "ray.h"

struct world;
class material;

struct rayHitInfo
{
	rayHitInfo();
	rayHitInfo(ray &incomingRay, world *worldToRender);
	rayHitInfo(ray &incomingRay, world *worldToRender, int reflectionNr);
	
	bool hitOccured;
	int reflectionNr; //parameter says which reflection the ray represents; stops infinite reflections
	float t;
	vector3 normal;
	vector3 hitPoint;
	vector3 sphericalAnisotropicVector;
	ray incomingRay;
	world *worldToRender;
	material *materialToShade;

	static float minIntersectionDistance; //distance used do avoid errors during intersections

	void setHit(float const &t, vector3 const &normal, material *materialToShade, vector3 const &localHitPoint);
	void setHitAnisotropicSphere(float const &t, vector3 const &normal, material *materialToShade, vector3 const &localHitPoint, vector3 const &anisotropicVector);
	vector3 globalHitPoint();
	void operator = (rayHitInfo &info);
};

