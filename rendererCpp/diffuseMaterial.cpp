#include "stdafx.h"
#include "diffuseMaterial.h"
#include "multipleObjectsTracer.h"

diffuseMaterial::diffuseMaterial(texture * materialTexture, float const &diffuseCoefficient):
	material(materialTexture),
	diffuseCoefficient(diffuseCoefficient)
{
}

vector3 diffuseMaterial::shade(rayHitInfo &info)
{
	ray rayToLightSource;

	//get color from ambient
	vector3 pixelColor(info.worldToRender->currentAmbientLight.getLight() * getTextureColor(info.hitPoint));

	//variables for use inside loop
	vector3 intersectionPoint;
	vector3 directionToLight;

	//licz� dla ka�dego �wiat�a w �wiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); ++i) {
		//find ray to light surce
		intersectionPoint = info.incomingRay.origin + info.incomingRay.direction*info.t;
		intersectionPoint = intersectionPoint + info.normal*shadowBias;
		directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		rayHitInfo tempInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits source
		multipleObjectsTracer::traceShadowRay(tempInfo, info.worldToRender->lightsInTheScene[i]);
		//kolor materia�u razy kolor �wiat�a w zale�no�ci od k�ta padania �wiat�a
		if (!tempInfo.hitOccured) {
			float dot = max(0.0f, info.normal.dot(directionToLight));
			pixelColor += getTextureColor(info.hitPoint) * dot * info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * diffuseCoefficient;
		}
	}
	return pixelColor;
}
