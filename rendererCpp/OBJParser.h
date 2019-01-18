#pragma once
#include "triangle.h"

class OBJParser
{
public:
	OBJParser();
	OBJParser(string pathToFile);

	bool readFile(string pathToFile);

	bool fileRead;
	material *defaultParserMaterial;
	vector <vector3> vertices;
	vector <vector3> normals;
	vector <triangle*> faces;
};

