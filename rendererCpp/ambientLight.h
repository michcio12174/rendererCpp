#pragma once

class ambientLight
{
public:
	ambientLight();
	ambientLight(vector3 color, float intensity);

	vector3 getLight();
	void operator = (ambientLight const &otherLight);

	vector3 color;
	float intensity;
};

