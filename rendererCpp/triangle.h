#pragma once
#include "plane.h"

class triangle :
	public plane
{
public:
	triangle(vector3 A, vector3 B, vector3 C, material *materialToUse) :
		plane(A, B, C, materialToUse),
		B(B),
		C(C) {}

	triangle(vertex A, vertex B, vertex C) :
		plane(A),
		B(B),
		C(C) {}

	triangle(vertex A, vertex B, vertex C, vector3 color) :
		plane(A),
		B(B),
		C(C),
		color(color) {}

	bool hit(rayHitInfo &info);

	vertex B;
	vertex C;
	//vector3 normal;
	vector3 color;
};

