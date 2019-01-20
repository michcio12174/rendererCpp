#include "stdafx.h"
#include "sphereAnisotropic.h"

sphereAnisotropic::sphereAnisotropic() : sphere()
{
	this->anisotropyVector = vector3();
}

sphereAnisotropic::sphereAnisotropic(vector3 origin, float radius, material * materialToUse, vector3 anisotropyVector)
	:sphere(origin, radius, materialToUse)
{
	this->anisotropyVector = anisotropyVector;
}

sphereAnisotropic::sphereAnisotropic(const sphereAnisotropic & sphere):
	sphere(sphere)
{
	this->anisotropyVector = sphere.anisotropyVector;
}

void sphereAnisotropic::hit(rayHitInfo & info)
{
	vector3 rayOriginMinusSphereOrigin = info.incomingRay.origin - origin;
	float b = rayOriginMinusSphereOrigin.dot(info.incomingRay.direction); //b w równaniu ax^2 + bx + c = 0
	float delta = b * b - rayOriginMinusSphereOrigin.dot(rayOriginMinusSphereOrigin) + radius * radius;

	if(delta >= 0.0001f) { //dwa przeciêcia, delta>0
		delta = sqrt(delta);
		float t1 = -b - delta;  //delta to pierwiastek, wiec zawsze dodatnia
		float t2 = -b + delta;  //st¹d zawsze t1<t2

		//je¿eli t = 0 to i tak nie uznajemy przeciêcia
		if (t2 < info.minIntersectionDistance) {
			return;
		}
		else if (t1 < info.minIntersectionDistance) {
			// - origin - przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
			vector3 intersection2 = info.incomingRay.origin + info.incomingRay.direction*t2 - origin;

			vector3 tempNormal(intersection2);
			tempNormal.normalize();

			info.setHitAnisotropicSphere(t2, tempNormal, materialToUse, intersection2, anisotropyVector);
		}
		else {
			// - origin - przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
			vector3 intersection1 = info.incomingRay.origin + info.incomingRay.direction*t1 - origin;

			vector3 tempNormal(intersection1);
			tempNormal.normalize();

			info.setHitAnisotropicSphere(t1, tempNormal, materialToUse, intersection1, anisotropyVector);
		}
	}
	else if (delta < 0.0001f && delta > -0.0001f) { //w praktyce jeœli delta=0 - jedno przeciêcie
		float t = -b;
		vector3 intersection = info.incomingRay.origin + info.incomingRay.direction*t;
		vector3 tempNormal = intersection - origin;
		tempNormal.normalize();

		//przekszta³cam globalny punkt na lokalny z pocz¹tkiem uk³adu w œrodku sfery
		intersection -= origin;

		info.setHitAnisotropicSphere(t, tempNormal, materialToUse, intersection, anisotropyVector);
	}
}