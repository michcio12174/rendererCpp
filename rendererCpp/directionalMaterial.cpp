#include "stdafx.h"
#include "directionalMaterial.h"


directionalMaterial::directionalMaterial(): material()
{
}

directionalMaterial::directionalMaterial(texture * materialTexture):
	material(materialTexture)
{
}

vector3 directionalMaterial::shade(rayHitInfo & info)
{
	return getTextureColor(info.hitPoint) * info.normal.dot(-info.incomingRay.direction);
}