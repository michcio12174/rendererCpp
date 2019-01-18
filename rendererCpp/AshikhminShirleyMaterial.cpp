#include "stdafx.h"
#include "AshikhminShirleyMaterial.h"
#include "multipleObjectsTracer.h"

float pi = 3.14159265359f;

AshikhminShirleyMaterial::AshikhminShirleyMaterial(texture * diffuseTexture, float specularCoeff, float diffuseCoeff, float horizontalCoefficient, float verticalCoefficient) :
	specularCoeff(specularCoeff),
	diffuseCoeff(diffuseCoeff),

	vCoeff(horizontalCoefficient),
	uCoeff(verticalCoefficient),

	diffuseTexture(diffuseTexture),
	specularTexture (new texture(0, 0, 0))
{
}

AshikhminShirleyMaterial::AshikhminShirleyMaterial(texture * diffuseTexture, texture * specularTexture, float specularCoeff, float diffuseCoeff, float horizontalCoefficient, float verticalCoefficient):
	specularCoeff(specularCoeff),
	diffuseCoeff(diffuseCoeff),

	vCoeff(horizontalCoefficient),
	uCoeff(verticalCoefficient),

	diffuseTexture(diffuseTexture),
	specularTexture(specularTexture)
{
}

AshikhminShirleyMaterial::AshikhminShirleyMaterial(texture * diffuseTexture, texture * specularTexture, float horizontalCoefficient, float verticalCoefficient):
	specularCoeff(1),
	diffuseCoeff(1),

	vCoeff(horizontalCoefficient),
	uCoeff(verticalCoefficient),

	diffuseTexture(diffuseTexture),
	specularTexture(specularTexture)
{
	//in the intersection point the u axis can be considered as horizontal and v as vertical
	//however values are interchanged in constructor
	//it is so because they are used to calculate exponent of result of a dot product of nornal and half vector
	//dot is between 0 and 1 and increases as the angle gets smaller
	//natural power of number x>0 && x<1 is always smaller than x
	//bigger exponent - weaker specular reflection in that point
	//smallest exponent and stronger specular when half vector is normal to the surface
	//if we go left on the sphere, angle with u vector dicreases, dot increses and exponent increases
	//this is why multiplying dot of half vector and u decreases specular reflection in direction of u
	//and why vCoeff = horizontalCoefficient and uCoeff = verticalCoefficient

	//so in fact uCoeff has horizontal and vCoeff vertical effects, but they are reversed 
	//smaller uCoeff = bigger horizontal reflection
	//the default specular is very big and I see no need to make it bigger
	//I also assume user will be instinctively inputting values above 1
	//so to achieve intuitive behavios of class
	//vCoeff = horizontalCoefficient and uCoeff = verticalCoefficient
	//not the other way around
	//therefore verticalCoefficient decreases horizontal specular and gives apperance of increased vertical specular
}

vector3 AshikhminShirleyMaterial::shade(rayHitInfo & info)
{
	ray rayToLightSource;

	//get color from ambient light
	vector3 pixelColor(info.worldToRender->getAmbientLight()*diffuseTexture->getColor(info.hitPoint));

	//variables for use inside loop
	vector3 intersectionPoint;
	vector3 directionToLight;

	//liczê dla ka¿dego œwiat³a w œwiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); ++i) {
		//find ray to light surce
		intersectionPoint = info.globalHitPoint() + info.normal*material::shadowBias;
		directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		rayHitInfo shadowRayInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits light source
		multipleObjectsTracer::traceShadowRay(shadowRayInfo, info.worldToRender->lightsInTheScene[i]);
		
		//if intercestion is not in shadow also get color from specular and diffuse shading
		if (!shadowRayInfo.hitOccured) {
			pixelColor += diffuseComponent(info, directionToLight, info.worldToRender->lightsInTheScene[i]) * diffuseCoeff
				+ specularComponent(info, directionToLight, info.worldToRender->lightsInTheScene[i]) * specularCoeff;
		}
	}
	return pixelColor;
}

vector3 AshikhminShirleyMaterial::diffuseComponent(rayHitInfo const &info, vector3 const &directionToLight, light * ligtToUse)
{
	vector3 specularColor = specularTexture->getColor(info.hitPoint);

	vector3 firstTerm = ((diffuseTexture->getColor(info.hitPoint) * 28) / (23 * pi)) * invertColor(specularColor);
	float secondTerm = 1 - pow(1 - (info.normal.dot(directionToLight)) / 2, 5);
	float thirdTerm = 1 - pow(1 - (info.normal.dot(-info.incomingRay.direction)) / 2, 5);

	return (firstTerm * secondTerm * thirdTerm) * ligtToUse->getLight(info.hitPoint);
}

vector3 AshikhminShirleyMaterial::specularComponent(rayHitInfo const &info, vector3 const &dirToLight, light * ligtToUse)
{
	vector3 hv = (dirToLight - info.incomingRay.direction); //half vector
	hv.normalize();

	//calculating local coordinates
	vector3 u = info.normal.cross(info.sphericalAnisotropicVector);
	vector3 v = info.normal.cross(u);

	vector3 specularColor = specularTexture->getColor(info.hitPoint);

	float firstTerm = sqrt((vCoeff + 1) * (uCoeff + 1)) / 8 * pi;
	float exponent = (0.5f*uCoeff * hv.dot(u) * hv.dot(u) + vCoeff * hv.dot(v) * hv.dot(v)) / (1 - pow(info.normal.dot(hv), 2));
	float secondTermNumerator = pow(info.normal.dot(hv), exponent);
	float secondTermDenominator = hv.dot(dirToLight) * max(info.normal.dot(dirToLight), info.normal.dot(-info.incomingRay.direction));
	vector3 FresnerFraction = specularColor + invertColor(specularColor) * pow(1 - dirToLight.dot(hv), 5);

	return (FresnerFraction * firstTerm * (secondTermNumerator / secondTermDenominator)) * ligtToUse->getLight(info.hitPoint);
}

vector3 AshikhminShirleyMaterial::invertColor(vector3 &colorToInvert) 
{
	return vector3(1 - colorToInvert.r, 1 - colorToInvert.g, 1 - colorToInvert.b);
}