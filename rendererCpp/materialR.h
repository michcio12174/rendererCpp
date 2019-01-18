#pragma once

enum class MaterialType
{
	MATTE = 1,
	REFLECTIVE = 2,
	REFRACTIVE = 3
};

struct materialR
{
	materialR();
    materialR(std::string name, MaterialType typeOfMaterial, float n);
    materialR(const vector4 &colorAmbient, MaterialType typeOfMaterial, float n);
    materialR(const materialR &newMaterial);

    materialR& operator=(const materialR &rhs);
	string toString();

    string name;
    vector4 colorAmbient;
    vector4 colorDiffuse;
    vector4 colorSpecular;
    vector4 colorEmissive;
    float ns;// Specular Highlight
    float ni;// Optical Density
    float d;// Dissolve
    float tr;
    vector3 tf;
    float illum;// Illumination

    float n;
    MaterialType typeOfMaterial;

    vector4 diffuseReflectionCoefficient;
    vector4 specularReflectionCoefficient;
};

