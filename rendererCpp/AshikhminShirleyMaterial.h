#pragma once
#include "material.h"
class AshikhminShirleyMaterial :
	public material
{
public:
	AshikhminShirleyMaterial(texture * diffuseTexture, float specularCoeff, float diffuseCoeff, float horizontalExponent, float verticalExponent);
	AshikhminShirleyMaterial(texture * diffuseTexture, texture * specularTexture, float specularCoeff, float diffuseCoeff, float horizontalExponent, float verticalExponent);
	AshikhminShirleyMaterial(texture * diffuseTexture, texture * specularTexture, float horizontalExponent, float verticalExponent);

	vector3 shade(rayHitInfo &info);

private:
	//uCoeff and vCoeff control anisotropy calculated for coordinate system local for each hit point
	//this system is comprized of u, v and n vectors, where n is normal in point of intersection
	float uCoeff, vCoeff; 
	float specularCoeff, diffuseCoeff;
	texture *specularTexture, *diffuseTexture;

	vector3 diffuseComponent(rayHitInfo const &info, vector3 const &directionToLight, light *ligtToUse);
	vector3 specularComponent(rayHitInfo const &info, vector3 const &directionToLight, light *ligtToUse);
	vector3 invertColor(vector3 &colorToInvert);
};