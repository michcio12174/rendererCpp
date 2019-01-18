#pragma once
#include "rayHitInfo.h"
#include "world.h"

class material;

struct multipleObjectsTracer
{
	static vector3 traceRay(rayHitInfo &info);
	static void traceShadowRay(rayHitInfo &info, light *lightToUse);
};

