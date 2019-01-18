#include "stdafx.h"
#include "transparentMaterial.h"
#include "multipleObjectsTracer.h"


transparentMaterial::transparentMaterial():
	indexOfRefraction(1)
{
}

transparentMaterial::transparentMaterial(float const &indexOfRefraction):
	indexOfRefraction(indexOfRefraction)
{
}

vector3 transparentMaterial::shade(rayHitInfo & info)
{
	if (info.reflectionNr < 5) {
		float n;
		vector3 normal(info.normal);
		vector3 intersection = info.incomingRay.origin + info.incomingRay.direction * info.t;

		float cosAlfaI = normal.dot(-info.incomingRay.direction);
		if (cosAlfaI < 0) {
			//jeśli kąt jest mniejszy od zera, to znaczy że jestem w środku sfety i z niej wychodzę 
			//należy odwrócić kąt i normalną
			cosAlfaI = -cosAlfaI;
			normal = -normal;
			n = info.worldToRender->indexOfRefraction / indexOfRefraction;
			//dbam o to, żeby punkt przecięcia by w po odpowiedniej stronie figury
			intersection += info.normal*shadowBias;
		}
		else { 
			n = indexOfRefraction / info.worldToRender->indexOfRefraction;
			//dbam o to, żeby punkt przecięcia by w po odpowiedniej stronie figury		
			intersection -= info.normal*shadowBias;
		}
		float temp = 1.0f - (1.0f - cosAlfaI*cosAlfaI) / (n*n);

		//if (temp >= 0) {
			float cosAlfaT = sqrt(temp);
			vector3 refractedDir = info.incomingRay.direction / n - normal*(cosAlfaT - cosAlfaI / n);

			ray refractedRay(intersection, refractedDir);
			rayHitInfo refractionInfo(refractedRay, info.worldToRender, info.reflectionNr + 1);
			return multipleObjectsTracer::traceRay(refractionInfo);
		//}
	}
	else return vector3(1, 1, 1);
}
