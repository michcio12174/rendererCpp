// rendererCpp.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include "sphereAnisotropic.h"
#include "triangle.h"
#include "rectangle.h"
#include "orthogonalCamera.h"
#include "perspectiveCamera.h"
#include "OBJParser.h"
#include "textureSpherical.h"
#include "saveToTGA.h"

#include "directionalMaterial.h"
#include "PhongMaterial.h"
#include "mirrorMaterial.h"
#include "transparentMaterial.h"
#include "AshikhminShirleyMaterial.h"

//axes are oriented in following way:
//			y
//			|
//			|
//			|
//			|__________x
//         /
//        /
//       /
//      z

//rasterizer - visible triangles are clockwise

//time-measuring functions and variables
void startTimer();
void stopTimer();

high_resolution_clock::time_point t1;
high_resolution_clock::time_point t2;

//funcje testuj¹ce raytracer
void task2();
void task3();
void task4();
void task5();
void task6();
void projekt();
//funkcje testuj¹ce rasteryzer
void matrixAlgebraTest();

//zmienne dla œwiata
int width = 800, height = 600;
ambientLight ambientL(vector3(1, 1, 1), 0.1f);
//world
world worldOne(ambientL);

//dane dla kamer
float zoom = 3.6f;
vector3 centerOfWievingPlane(0, 0, 60, false);
vector3 lookat(0, 0, 0, false);

int main()
{
	//raytracer
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	projekt();
	//matrixAlgebraTest();

	/*int x = 0;
	unsigned char a = 0, r = 0, g = 0, b = 255;
	x |= (a << 24);
	x |= (r << 16);
	x |= (g << 8);
	x |= (b);
	cout << (int)b << endl;
	for (int i = 7; i >= 0; i--)
		cout << ((b >> i) & 1);

	cout<<endl << x << endl;
	for (int i = 31; i >= 0; i--)
		cout << ((x >> i) & 1);

	cin >> x;*/
}

void startTimer() {
	t1 = high_resolution_clock::now();
}

void stopTimer() {
	t2 = high_resolution_clock::now();
	duration<float> duration = t2 - t1;
	cout << "render time: " << duration.count() << endl;
	cout << "FPS: " << 1 / duration.count() << endl;
}

void matrixAlgebraTest() {
	vector3 z3(1, 2, 1);
	vector4 z4(1, 2, 1, 1);

	vector4 A1(1, 2, 3, 2);
	vector4 A2(3, 4, 0, 1);
	vector4 A3(1, 3, 4, 2);
	vector4 A4(1, 2, 4, 2);

	float4x4 A(A1, A2, A3, A4);

	cout << A.toString() << endl;

	cout << "V3: " << (z3*=A).toString() << " v3: " << z3.toString() << endl;
	cout << "V4: " << (z4*=A).toString() << " v4: " << z4.toString() << endl;
	int asd;
	cin >> asd;
}

void projekt() {
	material *black = new material(new texture(0, 0, 0));
	material *blue = new PhongMaterial(new texture(0, 0, 1), 1);
	material *green = new PhongMaterial(new texture(0, 1, 0), 1);
	material *white = new PhongMaterial(new texture(1, 1, 1), 1);
	material *grey = new PhongMaterial(new texture(0.6f, 0.6f, 0.6f), 1);
	material *yellow = new PhongMaterial(new texture(1, 1, 0), 1);
	material *red = new PhongMaterial(new texture(1, 0, 0), 3, 5, 1);

	texture diffuseTexture(1, 0, 0);
	texture diffuseTexture1(0, 0.3f, 0);
	texture specularTexture(0.1f, 0.1f, 0.1f);
	texture specularTexture1(0.1f, 0, 0.2f);
	vector3 anisotropyVector = vector3(0, 1, 0, true);
	vector3 anisotropyVector1 = vector3(0, 1, 0, true);
	vector3 anisotropyVector2 = vector3(0, 1, 0, true);
	vector3 anisotropyVector3 = vector3(0, 1, 0, true);
	material *ASred = new AshikhminShirleyMaterial(&diffuseTexture, &specularTexture, 500, 500);
	material *ASred1 = new AshikhminShirleyMaterial(&diffuseTexture, &specularTexture, 300, 30);
	material *ASred2 = new AshikhminShirleyMaterial(&diffuseTexture1, &specularTexture1, 500, 200);
	material *ASred3 = new AshikhminShirleyMaterial(&diffuseTexture1, &specularTexture1, 1, 1);


	//lights
	float ligtIntensity = 10000.0f;
	vector3 lightColor(1, 1, 1);

	vector3 lightCenter(-2, 100, 102, false);
	light l(lightColor, ligtIntensity, lightCenter);
	worldOne.addLight(&l);

	vector3 lightCenter1(2, 100, 102, false);
	light l1(lightColor, ligtIntensity, lightCenter1);
	worldOne.addLight(&l1);

	vector3 lightCenter2(-2, 100, 98, false);
	light l2(lightColor, ligtIntensity, lightCenter2);
	worldOne.addLight(&l2);

	vector3 lightCenter3(2, 100, 98, false);
	light l3(lightColor, ligtIntensity, lightCenter3);
	worldOne.addLight(&l3);


	//geometric objects
	float radius = 40;
	vector3 center(135, -10, -60, false);
	sphere redSphere(center, radius, red);
	worldOne.addObject(&redSphere);

	/*vector3 centerASred(0, -10, -60, false);
	sphereAnisotropic redSphereAS(centerASred, radius, ASred, anisotropyVector);
	worldOne.addObject(&redSphereAS);*/

	vector3 centerASred1(45, -10, -60, false);
	sphereAnisotropic redSphereAS1(centerASred1, radius, ASred1, anisotropyVector1);
	worldOne.addObject(&redSphereAS1);

	vector3 centerASred2(-45, -10, -60, false);
	sphereAnisotropic redSphereAS2(centerASred2, radius, ASred2, anisotropyVector2);
	worldOne.addObject(&redSphereAS2);

	vector3 centerASred3(-135, -10, -60, false);
	sphereAnisotropic redSphereAS3(centerASred3, radius, ASred3, anisotropyVector3);
	worldOne.addObject(&redSphereAS3);

	//box
	vector3 normalr(1, 0, 0, true);
	vector3 pointr(-180, 0, 0, false);
	plane redPlane(pointr, normalr, red);
	worldOne.addObject(&redPlane);

	vector3 normalb(-1, 0, 0, true);
	vector3 pointb(180, 0, 0, false);
	plane bluePlane(pointb, normalb, blue);
	worldOne.addObject(&bluePlane);

	vector3 normalw(0, 0, 1, true);
	vector3 pointw(0, 0, -200, false);
	plane whitePlane(pointw, normalw, yellow);
	worldOne.addObject(&whitePlane);

	vector3 normalCeiling(0, -1, 0, true);
	vector3 pointCeiling(0, 210, 0, false);
	plane ceiling(pointCeiling, normalCeiling, black);
	worldOne.addObject(&ceiling);

	vector3 normalBlackWall(0, 0, -1, true);
	vector3 pointBlackWall(0, 0, 20, false);
	plane blackWall(pointBlackWall, normalBlackWall, black);
	//worldOne.addObject(&blackWall);

	//p³aszczyzna, na której stoj¹ figury
	vector3 A(-180, -100, 100, false);
	vector3 B(180, -100, 100, false);
	vector3 C(180, -100, -200, false);
	vector3 D(-180, -100, -200, false);
	triangle triangle1(A, B, C, grey);
	worldOne.addObject(&triangle1);
	triangle triangle2(A, D, C, grey);
	worldOne.addObject(&triangle2);

	//cameras
	/*CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	cameraO.setResolution(width, height);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../Images/renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");*/

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 200);
	cameraP.setResolution(width, height);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../Images/renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");

	while (!windowP.is_closed()) {
		windowP.wait();
	}
}

void task6() {
	material *black = new material(new texture(0, 0, 0));
	material *blue = new PhongMaterial(new texture(0, 0, 1), 1);
	material *red = new PhongMaterial(new texture(1, 0, 0), 0.1f);
	material *green = new PhongMaterial(new texture(0, 1, 0), 1);
	material *white = new PhongMaterial(new texture(1, 1, 1), 1);
	material *grey = new PhongMaterial(new texture(0.6f, 0.6f, 0.6f), 1);
	material *yellow = new PhongMaterial(new texture(1, 1, 0), 1);
	material *reflective = new mirrorMaterial();
	material *transparent = new transparentMaterial(3.5);

	//light
	vector3 lightColor(1, 1, 1);
	vector3 lightCenter(0, 100, -100, false);
	light l(lightColor, 10000, lightCenter);
	worldOne.addLight(&l);

	//geometric objects
	vector3 centerReflective(-105, 0, -140, false);
	float radiusReflective = 50;
	sphere reflectiveSphere(centerReflective, radiusReflective, reflective);
	worldOne.addObject(&reflectiveSphere);

	vector3 centerRefractive(40, 0, -50, false);
	float radiusRefractive = 50;
	sphere refractiveSphere(centerRefractive, radiusRefractive, transparent);
	worldOne.addObject(&refractiveSphere);

	/*vector3 center(130, -20, -90, false);
	float radius = 40;
	sphere redSphere(center, radius, red);
	worldOne.addObject(&redSphere);

	vector3 center3(-75, -10, -90, false);
	float radius3 = 15;
	sphere whiteSphere1(center3, radius3, white);
	worldOne.addObject(&whiteSphere1);

	vector3 center1(-110, -20, -90, false);
	float radius1 = 40;
	sphere blueSphere(center1, radius1, blue);
	worldOne.addObject(&blueSphere);

	vector3 center2(95, -10, -90, false);
	float radius2 = 15;
	sphere whiteSphere(center2, radius2, white);
	worldOne.addObject(&whiteSphere);*/


	//box
	vector3 normalr(1, 0, 0, true);
	vector3 pointr(-180, 0, 0, false);
	plane redPlane(pointr, normalr, red);
	worldOne.addObject(&redPlane);

	vector3 normalb(-1, 0, 0, true);
	vector3 pointb(180, 0, 0, false);
	plane bluePlane(pointb, normalb, blue);
	worldOne.addObject(&bluePlane);

	vector3 normalw(0, 0, 1, true);
	vector3 pointw(0, 0, -200, false);
	plane whitePlane(pointw, normalw, yellow);
	worldOne.addObject(&whitePlane);

	vector3 normalCeiling(0, -1, 0, true);
	vector3 pointCeiling(0, 210, 0, false);
	plane ceiling(pointCeiling, normalCeiling, black);
	worldOne.addObject(&ceiling);

	vector3 normalBlackWall(0, 0, -1, true);
	vector3 pointBlackWall(0, 0, 20, false);
	plane blackWall(pointBlackWall, normalBlackWall, black);
	worldOne.addObject(&blackWall);

	//p³aszczyzna, na której stoj¹ figury
	vector3 A(-180, -100, 100, false);
	vector3 B(180, -100, 100, false);
	vector3 C(180, -100, -200, false);
	vector3 D(-180, -100, -200, false);
	triangle triangle1(A, B, C, grey);
	worldOne.addObject(&triangle1);
	triangle triangle2(A, D, C, grey);
	worldOne.addObject(&triangle2);

	//cameras
	CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../Images/renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 200);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../Images/renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");

	while (!windowO.is_closed() && !windowP.is_closed()) {
		windowO.wait();
	}
}

void task5() {
	material *grey;
	material *earthMaterial;
	material *rectangleMaterial;

	textureSpherical earthTexture("../Images/earth.bmp", 90);
	texture rectangleTexture("../Images/earth.bmp", false);

	earthMaterial = new PhongMaterial(&earthTexture, 0.5f);
	rectangleMaterial = new PhongMaterial(&rectangleTexture, 0.5f);
	grey = new PhongMaterial(new texture(0.6f, 0.6f, 0.6f), 1);

	//light
	vector3 lightColor(1, 1, 1);
	vector3 lightCenter(-1, -1, -1, false);
	light l(lightColor, lightCenter);
	worldOne.addLight(&l);

	/*vector3 lightColor(1, 1, 1);
	vector3 lightCenter(100, 100, 40, false);
	light l(lightColor, 10000, lightCenter);
	worldOne.addLight(&l);*/

	//globe
	vector3 center(0, 0, -80, false);
	float radius = 60;
	sphere globe(center, radius, earthMaterial);
	worldOne.addObject(&globe);

	//rectangle
	vector3 rectangleeftUpperCorner(-400, 150, -150, false);
	rectangle texturedRectangle(rectangleeftUpperCorner, 800, 400, rectangleMaterial);
	worldOne.addObject(&texturedRectangle);

	//p³aszczyzna, na której stoj¹ figury
	vector3 A(-180, -50, 0, false);
	vector3 B(180, -50, 0, false);
	vector3 C(180, -50, -200, false);
	vector3 D(-180, -50, -200, false);
	triangle triangle1(A, B, C, grey);
	worldOne.addObject(&triangle1);
	triangle triangle2(A, D, C, grey);
	worldOne.addObject(&triangle2);

	//cameras
	CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	cameraO.setResolution(width, height);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../Images/renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 100);
	cameraP.setResolution(width, height);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../Images/renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");

	while (!windowO.is_closed() && !windowP.is_closed()) {
		windowP.wait();
	}
}

void task4() {
	material *blue;
	material *red;
	material *green;
	material *white;
	material *grey;

	boolean usePhongMaterial = true;

	if (usePhongMaterial) {
		blue = new PhongMaterial(new texture(0, 0, 1), 1);
		red = new PhongMaterial(new texture(1, 0, 0), 0.5f);
		green = new PhongMaterial(new texture(0, 1, 0), 1);
		white = new PhongMaterial(new texture(1, 1, 1), 1);
		grey = new PhongMaterial(new texture(0.6f, 0.6f, 0.6f), 1);
	}
	else
	{
		blue = new diffuseMaterial(new texture(0, 0, 1), 1);
		red = new directionalMaterial(new texture(1, 0, 0));
		green = new diffuseMaterial(new texture(0, 1, 0), 1);
		white = new material(new texture(1, 1, 1));
		grey = new diffuseMaterial(new texture(0.6f, 0.6f, 0.6f), 1);

	}

	//lights
	vector3 lightColor(1, 1, 1);
	vector3 lightCenter(100, 100, 40, false);
	light l(lightColor, 10000, lightCenter);
	worldOne.addLight(&l);

	vector3 lightCenter1(100, 100, 35, false);
	light l1(lightColor, 10000, lightCenter1);
	worldOne.addLight(&l1);

	vector3 lightCenter2(100, 100, 45, false);
	light l2(lightColor, 10000, lightCenter2);
	worldOne.addLight(&l2);

	//geometric objects
	vector3 center(-60, 40, -40, false);
	float radius = 40;
	sphere redSphere(center, radius, red);
	worldOne.addObject(&redSphere);

	vector3 center1(60, 40, -40, false);
	float radius1 = 40;
	sphere blueSphere(center1, radius1, blue);
	worldOne.addObject(&blueSphere);

	vector3 center2(30, 50, -40, false);
	float radius2 = 20;
	sphere whiteSphere(center2, radius2, white);
	worldOne.addObject(&whiteSphere);

	vector3 normal(0, 0, 1, true);
	vector3 point(0, 20, -60, false);
	plane greenPlane(point, normal, green);
	worldOne.addObject(&greenPlane);

	//p³aszczyzna, na której stoj¹ figury
	vector3 A(-180, -20, 0, false);
	vector3 B(180, -20, 0, false);
	vector3 C(180, -20, -200, false);
	vector3 D(-180, -20, -200, false);
	triangle triangle1(A, B, C, grey);
	worldOne.addObject(&triangle1);
	triangle triangle2(A, D, C, grey);
	worldOne.addObject(&triangle2);

	//cameras
	CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	cameraO.setResolution(width, height);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../Images/renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 100);
	cameraP.setResolution(width, height);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../Images/renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");

	while (!windowO.is_closed() && !windowP.is_closed()) {
		windowO.wait();
	}
}

void task3() {

	//create parser object that loads things into given world
	OBJParser parser("..\\MLRS.obj");
	//add faces to world
	material asergsadfg(new texture(1, 0.5, 0.5));

	int facesNr = parser.faces.size();
	for (int i = 0; i < facesNr; ++i) {
		worldOne.addObject(parser.faces[i]);
	}

	//cameras
	CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	cameraO.setResolution(width, height);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 100);
	cameraP.setResolution(width, height);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");

	while (!windowO.is_closed() && !windowP.is_closed()) {
		windowO.wait();
	}
}

void task2() {
	material blue(new texture(0, 0, 1));
	material red(new texture(1, 0, 0));
	material green(new texture(0, 1, 0));
	material white(new texture(1, 1, 1));
	material grey(new texture(0.6f, 0.6f, 0.6f));

	vector3 lightColor(1, 1, 1);
	vector3 lightCenter(100, 100, 40, false);
	light l(lightColor, 10000, lightCenter);
	worldOne.addLight(&l);

	vector3 center(-60, 40, -40, false);
	float radius = 40;
	sphere redSphere(center, radius, &red);
	worldOne.addObject(&redSphere);

	vector3 center1(60, 40, -40, false);
	float radius1 = 40;
	sphere blueSphere(center1, radius1, &blue);
	worldOne.addObject(&blueSphere);

	vector3 center2(30, 50, -40, false);
	float radius2 = 20;
	sphere whiteSphere(center2, radius2, &white);
	worldOne.addObject(&whiteSphere);

	vector3 normal(0, 0, 1, true);
	vector3 point(0, 20, -40, false);
	plane greenPlane(point, normal, &green);
	worldOne.addObject(&greenPlane);

	//cameras
	CImg<unsigned char> renderedSceneO(width, height, 1, 3, 0);
	orthogonalCamera cameraO(centerOfWievingPlane, lookat, zoom, &worldOne);
	startTimer();
	renderedSceneO = cameraO.renderImage();
	stopTimer();
	renderedSceneO.save("../renderedSceneO.bmp");
	CImgDisplay windowO(renderedSceneO, "Orthogonal");

	CImg<unsigned char> renderedSceneP(width, height, 1, 3, 0);
	perspectiveCamera cameraP(centerOfWievingPlane, lookat, zoom, &worldOne, 100);
	startTimer();
	renderedSceneP = cameraP.renderImage();
	stopTimer();
	renderedSceneP.save("../renderedSceneP.bmp");
	CImgDisplay windowP(renderedSceneP, "Perspective");
	
	while (!windowO.is_closed() && !windowP.is_closed()) {
		windowO.wait();
	}
}