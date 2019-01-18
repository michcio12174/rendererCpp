#include "stdafx.h"
#include "mirrorMaterial.h"
#include "multipleObjectsTracer.h"

mirrorMaterial::mirrorMaterial()
{
}

vector3 mirrorMaterial::shade(rayHitInfo & info)
{
	if (info.reflectionNr < 5) {
		vector3 intersection = info.incomingRay.origin + info.incomingRay.direction * info.t;
		intersection += info.normal*shadowBias;
		//by uzyskaæ wektor odbity potrzebny jest wektor nadchodz¹cy
		ray reflectedRay(intersection, info.incomingRay.direction.reflect(info.normal));
		rayHitInfo reflectionInfo(reflectedRay, info.worldToRender, info.reflectionNr + 1);
		return multipleObjectsTracer::traceRay(reflectionInfo);
	}
	
	return vector3(1, 1, 1);
}
