#include "stdafx.h"
#include "specularMaterial.h"
#include "multipleObjectsTracer.h"


specularMaterial::specularMaterial():
	material()
{
	this->highlightIntensity = 0.5;
	this->highlightSize = 100;
}

specularMaterial::specularMaterial(texture * materialTexture, float const &highlightIntensity, float const &highlightSize):
	material(materialTexture),
	highlightIntensity(highlightIntensity),
	highlightSize(highlightSize)
{
}

vector3 specularMaterial::shade(rayHitInfo & info)
{
	ray rayToLightSource;

	//get color from ambient light
	vector3 pixelColor(info.worldToRender->currentAmbientLight.getLight() * getTextureColor(info.hitPoint));

	//variables for use inside loop
	vector3 intersectionPoint;
	vector3 directionToLight;
	vector3 reflectionVector;

	//liczê dla ka¿dego œwiat³a w œwiecie
	for (int i = 0; i < info.worldToRender->lightsInTheScene.size(); ++i) {
		//find ray to light surce
		intersectionPoint = info.incomingRay.origin + info.incomingRay.direction*info.t;
		intersectionPoint += info.normal*shadowBias;
		directionToLight = info.worldToRender->lightsInTheScene[i]->getVectorToLight(intersectionPoint);
		rayHitInfo tempInfo(ray(intersectionPoint, directionToLight), info.worldToRender);

		//trace ray to see if it hits source
		multipleObjectsTracer::traceShadowRay(tempInfo, info.worldToRender->lightsInTheScene[i]);
		//liczymy tylko wartoœæ rozb³ysku zale¿nego od koloru œwiat³a
		//w ten sposób mo¿na go zsumowaæ w klasach dziedizcz¹cych z tej (dodaæ do diffuse w Phongu)
		//kolor materia³u dla materia³u tylko specularowego jest dodawany w funkcji shade powy¿ej
		if (!tempInfo.hitOccured) {
			reflectionVector = -directionToLight - info.normal * (info.normal.dot(-directionToLight) * 2);
			float RdotV = max(0.0f, (-info.incomingRay.direction).dot(reflectionVector));
			pixelColor += info.worldToRender->lightsInTheScene[i]->getLight(info.hitPoint) * (highlightIntensity * pow(RdotV, highlightSize));
		}
	}
	return pixelColor;
}