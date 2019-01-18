#include "stdafx.h"
#include "OBJParser.h"
#include "directionalMaterial.h"
#include "PhongMaterial.h"

OBJParser::OBJParser()
{
	//this material will be assigned to all objects from OBJ file
	defaultParserMaterial = new directionalMaterial(new texture(1, 0.5, 0.5));
}

OBJParser::OBJParser(string pathToFile)
{
	//this material will be assigned to all objects from OBJ file
	defaultParserMaterial = new directionalMaterial(new texture(1, 0.5, 0.5));
	//readFile(pathToFile);
}

bool OBJParser::readFile(string pathToFile)
{

	FILE *file = NULL;
	file = fopen(pathToFile.c_str(), "r");
	if (file == NULL) {
		fileRead = false;
		cout << "error while reading file" << endl;
		return false;
	}
	fileRead = true;

	char lineBeginning[5];
	int temp; 

	do {
		//s oznacza, ¿e szukamy ci¹gu znaków, których koñcem bêdzie znak bia³y
		temp = fscanf(file, "%s", lineBeginning);
		if (temp != EOF) {

			if (strcmp(lineBeginning, "v") == 0) {
				vector3 vertice;
				fscanf(file, "%f %f %f\n", &vertice.x, &vertice.y, &vertice.z);
				vertices.push_back(vertice);
			}

			else if (strcmp(lineBeginning, "vn") == 0) {
				vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normal.normalize();
				normals.push_back(normal);
			}

			else if (strcmp(lineBeginning, "f") == 0) {
				bool lineRead = false;
				int A, B, C, normal, At, Bt, Ct;
				//after f there is info about vertex, texture, normal in form of 
				//f 40/2/27 21/2/27 54/2/27 56/2/27 where we have vertex/texture/normal
				//if there is no texture they will look as follows: 
				//f 40//27 21//27 54//27 56//27

				/*if (fscanf(file, "%i/%i/%i %i/%i/%i %i/%i/%i\n", &A, &At, &normal, &B, &Bt, &normal, &C, &Ct, &normal) == 9)
				{
					lineRead = true;
					cout << "yesss" << endl;
				}
				else  cout << "parser jest za g³upi na ten plik" << endl;*/

				if (fscanf(file, "%i//%i %i//%i %i//%i\n", &A, &normal, &B, &normal, &C, &normal) == 6)
				{
					lineRead = true;
					cout << "yesss" << endl;
				}
				else  cout << "parser jest za g³upi na ten plik" << endl;

				if (lineRead) { 
					triangle *face = new triangle(vertices[A - 1], vertices[B - 1], vertices[C - 1], defaultParserMaterial);
					faces.push_back(face);
				}
			}
		}
	} while (temp != EOF);
	fclose(file);
	return true;
}
