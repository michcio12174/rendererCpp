#include "stdafx.h"
#include "plane.h"

plane::plane(vector3 point, vector3 normal, material *materialToUse):
	A(point)
{
	this->normal = normal;
	this->materialToUse = materialToUse;
}

plane::plane(vector3 point1, vector3 point2, vector3 point3, material *materialToUse):
	A(point1)
{
	//obliczam normalkê
	vector3 temp1 = point2 - point1;
	vector3 temp2 = point3 - point1;
	this->normal = temp1.cross(temp2);
	this->normal.normalize();

	this->materialToUse = materialToUse;
}

plane::plane(vertex point1):
	A(point1)
{
}

plane::plane(const plane &p):
	A(p.A),
	normal(p.normal)
{
}

bool plane::hit(rayHitInfo &info)
{
	//jeœli ray nadchodzi od strony po której jest normalka, to k¹t miêdzy direction a normal wyniesie ponad 180 stopni
	//dlatego zwracam odwrotn¹ normalkê - choæby by przesun¹æ punkt cieniowania do obserwatora a nie od niego
	float normalDotIncomingRay = normal.dot(info.incomingRay.direction);

	if (normalDotIncomingRay != 0) {
		float t = (normal.dot(this->A.position - info.incomingRay.origin)) / normalDotIncomingRay;

		if (t >= info.minIntersectionDistance) {
			//nast¹pi³o przeciêcie
			vector3 intersection = info.incomingRay.origin + info.incomingRay.direction * t;

			if (normalDotIncomingRay > 0) info.setHit(t, -normal, materialToUse, intersection);
			else info.setHit(t, normal, materialToUse, intersection);
			return true;
		}
	}
	//ray i wektor s¹ rownolegle
	return false;
}
