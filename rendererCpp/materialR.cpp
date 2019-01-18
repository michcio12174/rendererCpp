#include "stdafx.h"
#include "materialR.h"


#define NFACTOR 2.24f
#define POWER_FACTOR 0.5f


materialR::materialR() :
	colorAmbient(1, 0, 0),
	typeOfMaterial(MaterialType::MATTE),
	n(NFACTOR),
	diffuseReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
	specularReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }


materialR::materialR(const vector4 &colorAmbient, MaterialType typeOfMaterial, float n) :
	colorAmbient(colorAmbient),
	colorDiffuse(colorAmbient),
	//colorSpecular(vector4::black),
	//colorEmissive(vector4::black),
	ns(10.0f),
	typeOfMaterial(typeOfMaterial),
	n(n),
	diffuseReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
	specularReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }

materialR::materialR(std::string name, MaterialType typeOfMaterial, float n) :
	name(name),
	typeOfMaterial(typeOfMaterial),
	n(n),
	diffuseReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR)),
	specularReflectionCoefficient(vector4(POWER_FACTOR, POWER_FACTOR, POWER_FACTOR))
{ }

materialR::materialR(const materialR &newMaterial) :
	name(newMaterial.name),
	colorAmbient(newMaterial.colorAmbient),
	colorDiffuse(newMaterial.colorDiffuse),
	colorSpecular(newMaterial.colorSpecular),
	colorEmissive(newMaterial.colorEmissive),
	n(newMaterial.n),
	ni(newMaterial.ni),
	ns(newMaterial.ns),
	d(newMaterial.d),
	tr(newMaterial.tr),
	tf(newMaterial.tf),
	illum(newMaterial.illum),
	typeOfMaterial(newMaterial.typeOfMaterial),
	diffuseReflectionCoefficient(newMaterial.diffuseReflectionCoefficient),
	specularReflectionCoefficient(newMaterial.specularReflectionCoefficient)
{ }

materialR& materialR::operator=(const materialR &rhs)
{
	name = rhs.name;
	colorAmbient = rhs.colorAmbient;
	colorDiffuse = rhs.colorDiffuse;
	colorSpecular = rhs.colorSpecular;
	colorEmissive = rhs.colorEmissive;
	n = rhs.n;
	ni = rhs.ni;
	ns = rhs.ns;
	d = rhs.d;
	tr = rhs.tr;
	tf = rhs.tf;
	illum = rhs.illum;
	typeOfMaterial = rhs.typeOfMaterial;
	diffuseReflectionCoefficient = rhs.diffuseReflectionCoefficient;
	specularReflectionCoefficient = rhs.specularReflectionCoefficient;

	return *this;
}

string materialR::toString()
{
	string description;
	description += "name: " + name + "\n";
	description += "colorAmbient: " + colorAmbient.toString() + "\n";
	description += "colorDiffuse: " + colorDiffuse.toString() + "\n";
	description += "colorSpecular: " + colorSpecular.toString() + "\n";
	description += "colorEmissive: " + colorEmissive.toString() + "\n";
	description += "ns: " + to_string(ns) + "\n";
	description += "ni: " + to_string(ni) + "\n";
	description += "d: " + to_string(d) + "\n";
	description += "tr: " + to_string(tr) + "\n";
	description += "tf: " + tf.toString() + "\n";
	description += "illum: " + to_string(illum) + "\n";
	return description;
}
