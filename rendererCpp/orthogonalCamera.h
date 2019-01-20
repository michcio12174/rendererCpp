#pragma once
#include "world.h"

class orthogonalCamera
{
public:
	orthogonalCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender);
	orthogonalCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender);

	void setZoom(float const &zoom);
	void setResolution(int const &width, int const &height);
	virtual CImg<unsigned char> renderImage();

protected:
	int width, height;
	float pixelSize;
	vector3 u, v, w, up;
	vector3 planeCenter, lookat;
	world* worldToRender;

	virtual vector3 antiAliase(float const &x, float const &y, float squareSize);
	ray rayToGlobal(ray &localRay);
	void computeUVW(vector3 &planeCenter, vector3 &lookat, vector3 &up);
};

