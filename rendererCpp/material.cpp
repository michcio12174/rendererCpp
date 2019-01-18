#include "stdafx.h"
#include "material.h"


material::material()
{
	this->materialTexture = new texture(0.4f, 0.4f, 0.4f);
}

material::material(texture *materialTexture)
{
	this->materialTexture = materialTexture;
}

vector3 material::shade(rayHitInfo &info)
{
	return getTextureColor(info.hitPoint);
}

vector3 material::getTextureColor(vector3 const &localHitPoint) const
{
	return materialTexture->getColor(localHitPoint);
}