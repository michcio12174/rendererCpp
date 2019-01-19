#include "stdafx.h"
#include "PhongMaterial.h"
#include "multipleObjectsTracer.h"

PhongMaterial::PhongMaterial(texture * materialTexture, float const &highlightSize):
	material(materialTexture),
	diffuseCoefficient(1),
	highlightSize(highlightSize),
	highlightIntensity(1)
{
}

PhongMaterial::PhongMaterial(texture * materialTexture, float const &specularCoefficient, float const &highlightSize, float const &diffuseCoefficient):
	material(materialTexture),
	diffuseCoefficient(diffuseCoefficient),
	highlightSize(highlightSize),
	highlightIntensity(specularCoefficient)
{
}

vector3 PhongMaterial::shade(rayHitInfo & info)
{
	//get color from ambient light
	vector3 pixelColor(info.worldToRender->getAmbientLight() * getTextureColor(info.hitPoint));

	//definition of helper variables used in the loop
	vector3 intersectionPoint;
	vector3 directionToLight;
	vector3 reflectionVector;
	vector3 light;

	//liczê dla ka¿dego œwiat³a w œwiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); ++i) {
		//find ray to light surce
		intersectionPoint = info.globalHitPoint() + info.normal * material::shadowBias;
		directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		rayHitInfo shadowRayInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits light source
		multipleObjectsTracer::traceShadowRay(shadowRayInfo, info.worldToRender->lightsInTheScene[i]);
		//if intercestion is not in shadow also get color from specular and diffuse shading
		if (!shadowRayInfo.hitOccured) {

			//specular helpers
			reflectionVector = -directionToLight - info.normal * (info.normal.dot(-directionToLight) * 2);
			float RdotV = max(0.0f, (-info.incomingRay.direction).dot(reflectionVector));

			light = info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint);

			pixelColor += light * (highlightIntensity * pow(RdotV, highlightSize)) //specular component
				+ getTextureColor(info.hitPoint) * max(0.0f, info.normal.dot(directionToLight)) * light * diffuseCoefficient; //diffuse component
		}
	}
	return pixelColor;
}