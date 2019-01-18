#include "stdafx.h"
#include "geometricObject.h"

geometricObject::geometricObject()
{
}

bool geometricObject::hit(rayHitInfo &info)
{
	return false;
}

void geometricObject::setMaterial(material *materialToSet)
{
	materialToUse = materialToSet;
}

material * geometricObject::getMaterial()
{
	return materialToUse;
}
