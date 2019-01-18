#pragma once
#include "texture.h"
class textureSpherical :
	public texture
{
public:
	textureSpherical();
	textureSpherical(string imagePath);
	textureSpherical(string imagePath, int horizontalRotationInDegrees);
	~textureSpherical();

	vector3 getColor(vector3 const &localHitPoint) const;

protected :
	float horizontalRotation;
};

