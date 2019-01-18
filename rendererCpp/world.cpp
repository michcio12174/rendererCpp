#include "stdafx.h"
#include "world.h"

world::world()
{
	this->minColorDistanceSquare = 1;
	this->maxAntialiasingIterations = 3;
	this->currentAmbientLight = ambientLight(vector3(1, 1, 1), 0.1f);
	indexOfRefraction = 1;
}

world::world(int maxAntialiasingIterations, int minColorDistance)
{
	this->minColorDistanceSquare = minColorDistance*minColorDistance;
	this->maxAntialiasingIterations = maxAntialiasingIterations;
	this->currentAmbientLight = ambientLight(vector3(1, 1, 1), 0.1f);
	indexOfRefraction = 1;
}

world::world(int maxAntialiasingIterations, int minColorDistance, ambientLight ambientToSet)
{
	this->minColorDistanceSquare = minColorDistance*minColorDistance;
	this->maxAntialiasingIterations = maxAntialiasingIterations;
	this->currentAmbientLight = ambientLight(ambientToSet);
	indexOfRefraction = 1;
}

void world::addObject(geometricObject *objectToAdd)
{
	objectsInTheScene.push_back(objectToAdd);
}

void world::addLight(light * lightToAdd)
{
	lightsInTheScene.push_back(lightToAdd);
}

void world::setAmbientLight(ambientLight lightToSet) 
{
	this->currentAmbientLight = lightToSet;
}

void world::setRefractionIndex(float index)
{
	indexOfRefraction = index;
}

vector3 world::getAmbientLight()
{
	return currentAmbientLight.getLight();
}
