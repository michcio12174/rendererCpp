#include "stdafx.h"
#include "geometricObject.h"

geometricObject::geometricObject()
{
}

void geometricObject::setMaterial(material *materialToSet)
{
	materialToUse = materialToSet;
}

material * geometricObject::getMaterial()
{
	return materialToUse;
}
