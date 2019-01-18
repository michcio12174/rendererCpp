#pragma once
#include "geometricObject.h"
#include "vertex.h"

class plane: public geometricObject
{
public:
	plane(vector3 point, vector3 normal, material *materialToUse);
	plane(vector3 point1, vector3 point2, vector3 point3, material *materialToUse);
	//constructor used for rasterizer triangle - it only needs the vertex as one of triangle's vertices
	plane(vertex point1); 
	plane(const plane &p);

	bool hit(rayHitInfo &info);

	//vertex insted vector3 used becouse triangle inheryts from this class and needs this point to be a vertex
	vertex A;
protected:
	vector3 normal;
};

