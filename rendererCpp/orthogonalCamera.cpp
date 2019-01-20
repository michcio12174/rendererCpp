#include "stdafx.h"
#include "orthogonalCamera.h"
#include "multipleObjectsTracer.h"

orthogonalCamera::orthogonalCamera(vector3 planeCenter, vector3 lookat, float zoom, world *worldToRender)
{
	//----------obliczam bazê ortonormaln¹ dla kamery
	computeUVW(planeCenter, lookat, vector3(0, 1, 0, false));
	//----------przypisujê wartoœæ pozosta³ym cz³onkom klasy
	this->planeCenter = planeCenter;
	this->lookat = lookat;
	this->worldToRender = worldToRender;
	this->width = 800;
	this->height = 600;
	this->pixelSize = 1 / zoom;

}

orthogonalCamera::orthogonalCamera(vector3 planeCenter, vector3 lookat, vector3 up, float zoom, world *worldToRender)
{
	//----------obliczam bazê ortonormaln¹ dla kamery
	computeUVW(planeCenter, lookat, up);
	//----------przypisujê wartoœæ pozosta³ym cz³onkom klasy
	this->planeCenter = planeCenter;
	this->lookat = lookat;
	this->worldToRender = worldToRender;
	this->width = 800;
	this->height = 600;
	this->pixelSize = 1 / zoom;
}

void orthogonalCamera::setZoom(float const &zoom)
{
	this->pixelSize = 1 / zoom;
}

void orthogonalCamera::setResolution(int const &width, int const &height)
{
	this->width = width;
	this->height = height;
}

CImg<unsigned char> orthogonalCamera::renderImage()
{
	CImg<unsigned char> renderedImage = CImg<unsigned char> (width, height, 1, 3, 0);

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			
			//computing local ray origin coordinates
			//nie t³umaczê origina na globalne, bo w antyaliasingu potrzebujê koordynatów lokalnych, 
			//¿eby wystrzeliæ lokalnie przesuniête promienie
			vector3 returnedColor = antiAliase(
				pixelSize*(width * 0.5f - i + 0.5f),       //x
				pixelSize*(height * 0.5f - j - 0.5f),      //y
				pixelSize);

			returnedColor.toEightBit();
			renderedImage(i, j, 0) = returnedColor.r;
			renderedImage(i, j, 1) = returnedColor.g;
			renderedImage(i, j, 2) = returnedColor.b;
		}
	}
	return renderedImage;
}

vector3 orthogonalCamera::antiAliase(float const &x, float const &y, float squareSize)
{
	squareSize *= 0.5;

	ray centerRay(vector3(x, y, 0, false), vector3(0, 0, 1, false)), AARay;
	rayHitInfo info(rayToGlobal(centerRay), worldToRender);
	vector3 centerColor = multipleObjectsTracer::traceRay(info);

	vector3 colors[4];
	for (int i = 0; i < 4; ++i) {
		AARay = centerRay;

		switch (i) {
		case 0:
			AARay.origin.x -= squareSize;
			AARay.origin.y -= squareSize;
			break;
		case 1:
			AARay.origin.x += squareSize;
			AARay.origin.y -= squareSize;
			break;
		case 2:
			AARay.origin.x -= squareSize;
			AARay.origin.y += squareSize;
			break;
		case 3:
			AARay.origin.x += squareSize;
			AARay.origin.y += squareSize;
			break;
		}
		info = rayHitInfo(rayToGlobal(AARay), worldToRender);
		colors[i] = multipleObjectsTracer::traceRay(info);
	}

	centerColor.r = (colors[0].r + colors[1].r + colors[2].r + colors[3].r) * 0.25f;
	centerColor.g = (colors[0].g + colors[1].g + colors[2].g + colors[3].g) * 0.25f;
	centerColor.b = (colors[0].b + colors[1].b + colors[2].b + colors[3].b) * 0.25f;

	return centerColor;
}

ray orthogonalCamera::rayToGlobal(ray &localRay) {
	//aby przekonwertowaæ punkt do przestrzeni globalnej potrzebujemy pomno¿æ go przez bazê ortonormaln¹ 
	//a potem dodaæ lokalizacjê pocz¹tku lokalnego uk³au we wspó³rzêdnych globalnych
	localRay.origin = (u*localRay.origin.x + v * localRay.origin.y + w * localRay.origin.z) + planeCenter;

	//w wypadku wektora dodawanie jest niepotrzebne, bo nie jest on osadzony w konkretnym punkcie przestrzeni
	localRay.direction = u * localRay.direction.x + v * localRay.direction.y + w * localRay.direction.z;
	localRay.direction.normalize();

	return localRay;
}

void orthogonalCamera::computeUVW(vector3 &planeCenter, vector3 &lookat, vector3 &up)
{
	//obliczam w, odpowiednik z
	w = lookat - planeCenter;
	w.normalize();
	//obliczam u, odpowiednik x
	u = up.cross(w);
	u.normalize();
	//obliczam v, odpowiednik y
	v = w.cross(u);

	cout << "u: " << u.toString() << endl;
	cout << "v: " << v.toString() << endl;
	cout << "w: " << w.toString() << endl << endl;

	if (planeCenter.x == lookat.x && planeCenter.z == lookat.z && planeCenter.y > lookat.y) { 
		// camera looking vertically down
		u = vector3(0, 0, 1, false);
		v = vector3(1, 0, 0, false);
		w = vector3(0, 1, 0, false);
	}

	if (planeCenter.x == lookat.x && planeCenter.z == lookat.z && planeCenter.y < lookat.y) { 
		// camera looking vertically up
		u = vector3(1, 0, 0, false);
		v = vector3(0, 0, 1, false);
		w = vector3(0, -1, 0, false);
	}
}
