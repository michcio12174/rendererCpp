#include "stdafx.h"
#include "sphere.h"

sphere::sphere(vector3 origin, float radius, material *materialToUse)
{
	this->origin = origin;
	this->radius = radius;
	this->materialToUse = materialToUse;
}

sphere::sphere(const sphere & sphere)
{
	this->origin = sphere.origin;
	this->radius = sphere.radius;
	this->materialToUse = sphere.materialToUse;
}

void sphere::hit(rayHitInfo &info)
{
	vector3 rayOriginMinusSphereOrigin = info.incomingRay.origin - origin;
	float b = rayOriginMinusSphereOrigin.dot(info.incomingRay.direction); //b w równaniu ax^2 + bx + c = 0
	float delta = b * b - rayOriginMinusSphereOrigin.dot(rayOriginMinusSphereOrigin) + radius * radius;


	if (delta >= 0.0001f) { //dwa przeciêcia, delta>0
		delta = sqrt(delta);
		float t1 = -b - delta;  //delta to pierwiastek, wiec zawsze dodatnia
		float t2 = -b + delta;  //st¹d zawsze t1<t2
		//cout << t1 << " - t1" <<endl<< t2 << " - t2" << endl;

		//je¿eli t = 0 to i tak nie uznajemy przeciêcia
		if (t2 < info.minIntersectionDistance) {
			return;
		}
		else if (t1 < info.minIntersectionDistance) {
			vector3 intersection2 = info.incomingRay.origin + info.incomingRay.direction*t2;
			vector3 tempNormal = intersection2 - origin;
			tempNormal.normalize();

			//przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
			intersection2 -= origin;
			cout << "hit" << endl;
			info.setHit(t2, tempNormal, materialToUse, intersection2);
		}
		else {
			vector3 intersection1 = info.incomingRay.origin + info.incomingRay.direction*t1;
			vector3 tempNormal = intersection1 - origin;
			tempNormal.normalize();

			//przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
			intersection1 -= origin;

			info.setHit(t1, tempNormal, materialToUse, intersection1);
		}
	}
	else if (delta < 0.0001f && delta > -0.0001f) { //w praktyce jeœli delta=0 - jedno przeciêcie
		float t = -b;
		vector3 intersection = info.incomingRay.origin + info.incomingRay.direction*t;
		vector3 tempNormal = intersection - origin;
		tempNormal.normalize();

		//przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
		intersection -= origin;

		info.setHit(t, tempNormal, materialToUse, intersection);
	}
}

vector3 sphere::getNormal(vector3 point)
{
	vector3 temp = point - origin;
	temp.normalize();
	return temp;
}
