#include "stdafx.h"
#include "perspectiveCamera.h"
#include "multipleObjectsTracer.h"

perspectiveCamera::perspectiveCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender, float distanceToEyepoint) 
	: orthogonalCamera(planeCenter, lookat, zoom, worldToRender)
{
	this->eyePoint = vector3(0, 0, -distanceToEyepoint, false);
}

perspectiveCamera::perspectiveCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender, float distanceToEyepoint) 
	: orthogonalCamera(planeCenter, lookat, up, zoom, worldToRender)
{
	this->eyePoint = vector3(0, 0, -distanceToEyepoint, false);
}

//metoda bierze wspó³rzêdne x oraz y na p³aszczyŸnie widzenia, przez które przejdzie centralny promieñ
//promienie nie s¹ równoleg³e, dlatego trzeba tworzyæ nowe z przesuniêtym punktem pocz¹tkowym
vector3 perspectiveCamera::antiAliase(float const &x, float const &y, float squareSize)
{
	float squareSizeHalf = squareSize / 2;

	ray centerRay = constructPerspectiveRay(x, y);
	rayHitInfo info(rayToGlobal(centerRay), worldToRender);
	vector3 centerColor = multipleObjectsTracer::traceRay(info);

	if (squareSize >= pixelSize) {
		vector3 colors[4];
		float tempx, tempy;
		for (int i = 0; i < 4; ++i) {
			tempx = centerRay.origin.x;
			tempy = centerRay.origin.y;

			switch (i) {
			case 0:
				tempx = x - squareSizeHalf;
				tempy = y - squareSizeHalf;
				break;
			case 1:
				tempx = x + squareSizeHalf;
				tempy = y - squareSizeHalf;
				break;
			case 2:
				tempx = x - squareSizeHalf;
				tempy = y + squareSizeHalf;
				break;
			case 3:
				tempx = x + squareSizeHalf;
				tempy = y + squareSizeHalf;
				break;
			}
			info = rayHitInfo(rayToGlobal(constructPerspectiveRay(tempx, tempy)), worldToRender);
			colors[i] = multipleObjectsTracer::traceRay(info);
		}

		centerColor.r = (colors[0].r + colors[1].r + colors[2].r + colors[3].r) * 0.25f;
		centerColor.g = (colors[0].g + colors[1].g + colors[2].g + colors[3].g) * 0.25f;
		centerColor.b = (colors[0].b + colors[1].b + colors[2].b + colors[3].b) * 0.25f;
	}

	return centerColor;
}

//funkcja tworzy promieñ maj¹cy pocz¹tek w eyePoint kamery 
//i przechodz¹cy przez punkt na p³aszczyŸnie widzenia o wspó³czêdnych x, y
//potrzebujê znaæ tylko x oraz y bo eyePoint oraz œrodek p³aszczyzny s¹ znane dla klasy
ray perspectiveCamera::constructPerspectiveRay(float const &x, float const &y)
{
	vector3 pointOnTheViewPlane = vector3(x, y, 0, false);
	vector3 rayDirection = pointOnTheViewPlane - eyePoint;
	return ray(pointOnTheViewPlane, rayDirection);
}