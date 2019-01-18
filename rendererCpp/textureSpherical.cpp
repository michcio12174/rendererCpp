#include "stdafx.h"
#include "textureSpherical.h"


textureSpherical::textureSpherical() : texture()
{
}

textureSpherical::textureSpherical(string imagePath): 
	texture(imagePath, false)
{
	horizontalRotation = 0;
}

textureSpherical::textureSpherical(string imagePath, int horizontalRotationInDegrees):
	texture(imagePath, false)
{
	if (horizontalRotationInDegrees > 360) horizontalRotationInDegrees = 360;
	if (horizontalRotationInDegrees < 0) horizontalRotationInDegrees = 0;
	horizontalRotation = horizontalRotationInDegrees / 360.0f;
}


textureSpherical::~textureSpherical()
{
}

vector3 textureSpherical::getColor(vector3 const &localHitPoint) const
{
	//alfa to k¹t w poziomie - w lokalnej p³aszczyŸnie xz
	//beta to k¹t w pionie - lokalna p³aszczyzna osi y oraz punktu przeciêcia

	float r = localHitPoint.length();
	float alfa = atan2(localHitPoint.x, localHitPoint.z);
	float beta = acos(localHitPoint.y / localHitPoint.length());

	if (alfa < 0) alfa += 2 * 3.14159265359f;

	//dodajê jak¹œ czêœæ 2*pi, ¿eby obróciæ teksturê w poziomie i dbam o to, by nie wyjœæ poza przedzia³ <0, 2*pi)
	alfa += 6.28318530718f * horizontalRotation;
	if (alfa >= 6.28318530718f) alfa -= 6.28318530718f;

	float u = alfa * 0.1591549430918953f;
	float v = beta / 3.14159265359f;

	int x = (int)(width - 1)*u;
	int y = (int)(height - 1)*v;
	
	vector3 textureColor = vector3((*image)(x, y, 0), (*image)(x, y, 1), (*image)(x, y, 2));
	textureColor.scaleToOne();
	return textureColor;
}
