#include "stdafx.h"
#include "rasterizer.h"

rasterizer::rasterizer(int width, int height) : 
	bufferInstance(new buffer(width, height)),
	VPInscance(new vertexProcessor())
{
}

void rasterizer::drawTriangle(triangle triangle)
{
	//processing vertices of the triangle
	cout << "A before: " << triangle.A.position.toString() << endl;
	triangle.A = VPInscance->transform(triangle.A);
	cout << "A after: " << triangle.A.position.toString() << endl;

	cout << "B before: " << triangle.B.position.toString() << endl;
	triangle.B = VPInscance->transform(triangle.B);
	cout << "B after: " << triangle.B.position.toString() << endl;

	cout << "C before: " << triangle.C.position.toString() << endl;
	triangle.C = VPInscance->transform(triangle.C);
	cout << "C after: " << triangle.C.position.toString() << endl;

	//calculating light in each vertex
	/*vector3 tc1 = vp.lt({ v1, n1, c1 }, *mat);
	vector3 tc2 = vp.lt({ v2, n2, c2 }, *mat);
	vector3 tc3 = vp.lt({ v3, n3, c3 }, *mat);*/

	//transform from canonical view to screen space
	float x1 = (triangle.A.position.x + 1) * bufferInstance->width / 2, //TO OPT
		  x2 = (triangle.B.position.x + 1) * bufferInstance->width / 2,
		  x3 = (triangle.C.position.x + 1) * bufferInstance->width / 2,
		  y1 = (triangle.A.position.y + 1) * bufferInstance->height / 2,
		  y2 = (triangle.B.position.y + 1) * bufferInstance->height / 2,
		  y3 = (triangle.C.position.y + 1) * bufferInstance->height / 2;

	//find rectangle inside of which the triangle resides to optimize further calculations
	float minx = max(min(min(x1, x2), x3), 0.0f),
		maxx = min(max(max(x1, x2), x3), bufferInstance->width - 1.0f),
		miny = max(min(min(y1, y2), y3), 0.0f),
		maxy = min(max(max(y1, y2), y3), bufferInstance->height - 1.0f);

	//constans usefull later
	//we need float before calculating lambdas
	//the lambdas are always smaller of equal 1
	//so if we calcuate using ints we will always get 1 or zero that only then will be cast to float
	float dx12 = x1 - x2,
		dx23 = x2 - x3,
		dx31 = x3 - x1,
		dy12 = y1 - y2,
		dy23 = y2 - y3,
		dy31 = y3 - y1;


	//topleft calculation
	//assumes the vertices are arranged clockwise (i guess)
	bool isTopLeft1 = false, isTopLeft2 = false, isTopLeft3 = false;
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) isTopLeft1 = true;
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) isTopLeft2 = true;
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) isTopLeft3 = true;

	for (int y = miny; y < maxy; y++) {//To OPT
		for (int x = minx; x < maxx; x++) {

			//checking if we are inside of the triangle
			//assuming clockwise triangles are facing the camera
			if (((!isTopLeft1 && dx12*(y - y1) - dy12*(x - x1) > 0) || (isTopLeft1 && dx12*(y - y1) - dy12*(x - x1) >= 0)) &&
				((!isTopLeft2 && dx23*(y - y2) - dy23*(x - x2) > 0) || (isTopLeft2 && dx23*(y - y2) - dy23*(x - x2) >= 0)) &&
				((!isTopLeft3 && dx31*(y - y3) - dy31*(x - x3) > 0) || (isTopLeft3 && dx31*(y - y3) - dy31*(x - x3) >= 0))) 
			{

				//we need to make sure right side is float from the begining
				//the lambdas are always smaller of equal 1, so int will give wrong results
				//so if we calcuate using ints we will always get 1 or zero that only then fill be cast to float
				float lambda1 = (dy23 * (x - x3) - dx23 * (y - y3)) / (-dy23 * dx31 + dx23 * dy31), //to opt dzielenie
					  lambda2 = (dy31 * (x - x3) - dx31 * (y - y3)) / (dy31 * dx23 - dx31 * dy23),
					  lambda3 = 1.0f - lambda1 - lambda2;

				//calculating depth (z) of the point based on lambdas and depth of triangle's vertices
				//lambdas are barycentric coordinates of the point in relation to those vertices
				float depth = lambda1 * triangle.A.position.z + lambda2 * triangle.B.position.z + lambda3 * triangle.C.position.z;

				if (depth >= 0 && depth < bufferInstance->getDepth(x, y)) 
				{//TO OPT liczê t¹ pozycjê tam teraz i jeszcze raz przy ustawianiu

					bufferInstance->write(x, y, triangle.color, depth);

				}
			}
		}
	}
}

void rasterizer::drawMesh(mesh meshToDraw)
{
	//cout << meshToDraw.triangles.size() <<"mesh size in rasterizer drawmesh";

	for (triangle currentTriangle : meshToDraw.triangles) {
		drawTriangle(currentTriangle);
	}
}

void rasterizer::render()
{
	VPInscance->calculateFinalTransformMatrix();

	//bufferInstance->fillBufferWithColor(vector3(1, 0, 0));
	for (mesh currentMesh : objectsInTheScene) {
		drawMesh(currentMesh);
	}
}

void rasterizer::addObject(mesh meshToDraw)
{
	objectsInTheScene.push_back(meshToDraw); //TO OPT
}

void rasterizer::saveToTGA()
{
	saveToTGA::saveImage(*bufferInstance);
}

void rasterizer::setAmbientLight(ambientLight l)
{
	VPInscance->setAmbientLight(l);
}

void rasterizer::addLight(light l)
{
	VPInscance->addLight(l);
}

void rasterizer::setPerspective(float fov, float aspect, float nearPlane_z, float farPlane_z)
{
	VPInscance->setPerspective(fov, aspect, nearPlane_z, farPlane_z);
}

void rasterizer::setLookAt(vector3 eye, vector3 target, vector3 up)
{
	VPInscance->setLookAt(eye, target, up);
}

void rasterizer::displayImages()
{
	bufferInstance->displayImages();
}
