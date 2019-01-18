#pragma once
#include "rayHitInfo.h"

class geometricObject
{
public:
	geometricObject();
	virtual bool hit(rayHitInfo &info);
	void setMaterial(material *materialToSet);
	material* getMaterial();
protected:
	material *materialToUse;
};

