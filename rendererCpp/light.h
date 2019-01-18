#pragma once

class light
{
public:
	//directional light constructor
	light(vector3 color, vector3 direction);
	//point light constructor
	light(vector3 color, float intensity, vector3 origin);

	virtual vector3 getLight(vector3 position);
	virtual vector3 getVectorToLight(vector3 position);

	//origin is used as origin of point light or direction of directional light
	vector3 color, origin;
	//this class can represent both directional and spot ligts
	bool isPointLight;
	float intensity;
};

