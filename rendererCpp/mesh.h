#pragma once

#include "triangle.h"
#include "materialR.h"

struct mesh
{
	void addTriangle(triangle trinagleToAdd);

	vector<triangle> triangles;
	vector3 center;
	materialR currentMaterial;
	vector<materialR> materials;
};

