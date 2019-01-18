#pragma once

#include "vertex.h"
#include "material.h"
#include "light.h"
#include "ambientLight.h"

class vertexProcessor
{
public:
	vertexProcessor();

	//processing vertices
	vector3 transform(vector3 position);//TO OPT przekazywanie argumentów
	vertex transform(vertex vertexToTransform);
	vector3 illuminate(vertex v, material mat);
	void setPerspective(float fov, float aspect, float nearPlane_z, float farPlane_z);
	void setLookAt(vector3 eye, vector3 target, vector3 up);
	void setIdentity();
	void translate(vector3 v);
	void rotate(vector3 axis, float angle);
	void scale(vector3 scale);
	void calculateFinalTransformMatrix();
	//adding lights
	void setAmbientLight(ambientLight l);
	void addLight(light l);

private:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;
	float4x4 finalTransformMatrix;

	ambientLight activeAmbientLight;
	vector<light> lightsInTheScene;
};

