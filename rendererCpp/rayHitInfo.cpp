#include "stdafx.h"
#include "rayHitInfo.h"

float rayHitInfo::minIntersectionDistance = 0.00001f;

rayHitInfo::rayHitInfo():
	t(0),
	hitOccured(false),
	worldToRender(NULL),
	materialToShade(NULL),
	reflectionNr(0)
{
}

rayHitInfo::rayHitInfo(ray & incomingRay, world *worldToRender):
	t(0),
	hitOccured(false),
	incomingRay(incomingRay),
	worldToRender(worldToRender),
	materialToShade(NULL),
	reflectionNr(0)
{
}

rayHitInfo::rayHitInfo(ray & incomingRay, world * worldToRender, int reflectionNr):
	t(0),
	hitOccured(false),
	incomingRay(incomingRay),
	worldToRender(worldToRender),
	materialToShade(NULL),
	reflectionNr(reflectionNr)
{
}

void rayHitInfo::operator=(rayHitInfo & info)
{
	this->t = info.t;
	this->hitOccured = info.hitOccured;
	this->normal = info.normal;
	this->hitPoint = info.hitPoint;
	this->sphericalAnisotropicVector = info.sphericalAnisotropicVector;
	this->incomingRay = info.incomingRay;
	this->worldToRender = info.worldToRender;
	this->materialToShade = info.materialToShade;
	this->reflectionNr = info.reflectionNr;
}

void rayHitInfo::setHit(float const &t, vector3 const &normal, material *materialToShade, vector3 const &localHitPoint)
{
	this->t = t;
	this->normal = normal;
	this->hitPoint = localHitPoint;
	this->hitOccured = true;
	this->materialToShade = materialToShade;
	this->sphericalAnisotropicVector = vector3(0, 1, 0, false);
}

void rayHitInfo::setHitAnisotropicSphere(float const &t, vector3 const &normal, material *materialToShade, vector3 const &localHitPoint, vector3 const &anisotropicVector)
{
	this->t = t;
	this->normal = normal;
	this->hitPoint = localHitPoint;
	this->hitOccured = true;
	this->materialToShade = materialToShade;
	this->sphericalAnisotropicVector = anisotropicVector;
}

vector3 rayHitInfo::globalHitPoint()
{
	return incomingRay.origin + incomingRay.direction*t;
}
