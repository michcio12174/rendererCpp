#pragma once
#include "ambientLight.h"
#include "light.h"
#include "geometricObject.h"

struct world
{
	world();
	world(ambientLight ambientToSet);

	void addObject(geometricObject *objectToAdd);
	void addLight(light *lightToAdd);
	void setAmbientLight(ambientLight lightToSet);
	void setRefractionIndex(float index);
	vector3 getAmbientLight();

	float indexOfRefraction; //index of refracion for the default substance in the world
	ambientLight currentAmbientLight;
	vector<geometricObject*> objectsInTheScene;
	vector<light*> lightsInTheScene;
};

