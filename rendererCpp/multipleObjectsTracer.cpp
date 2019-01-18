#include "stdafx.h"
#include "multipleObjectsTracer.h"
#include "material.h"

vector3 multipleObjectsTracer::traceRay(rayHitInfo &info)
{
	//info to informacja o najbli�szym przeci�ciu, temp to informacja o przeci�ziu w aktualej iteracji p�tli
	rayHitInfo temp = info; 
	//if (info.worldToRender) {//to increase performance
		for (geometricObject *currentObject : info.worldToRender->objectsInTheScene) {
			currentObject->hit(temp);
			//zmieniamy info na temp je�li nie by�o jeszcze trafienia lub trafienie by�o dalej od kamery
			if (temp.hitOccured && (!info.hitOccured || temp.t < info.t)) {
				info = temp;
			}
		}
	//}
	//else cout << "null world pointer" << endl;

	if (info.materialToShade) return info.materialToShade->shade(info);
	else return vector3(0, 0, 0);
}

void multipleObjectsTracer::traceShadowRay(rayHitInfo & info, light *lightToUse)
{
	int size = info.worldToRender->objectsInTheScene.size();
	
	//funkcje hit ustawiaj� info o przeci�ciu tylko je�li jest trafienie
	rayHitInfo temp = info;
	//if (info.worldToRender) {//to increase performance
		//if a light is a point light, we check if there was a hit between light origin and shaded point
		if (lightToUse->isPointLight) {
			float distanceToLightSource = (lightToUse->origin - info.incomingRay.origin).x / info.incomingRay.direction.x;
			//wychodzimy z p�tli od tazu kiedy by�o przeci�cie, nie trzeba sprawdza� innych obiekt�w
			for (int i = 0; i < size && !info.hitOccured; ++i) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				//we change info only if hit in temp is between light source and shadow ray origin
				if (temp.t < distanceToLightSource)
					info = temp;
			}
		}
		//if a light is a directional light we check if there is any hit starting from shaded point in inverse direction of light
		else {
			//wychodzimy z p�tli od razu kiedy by�o przeci�cie, nie trzeba sprawdza� innych obiekt�w
			for (int i = 0; i < size && !info.hitOccured; ++i) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				if (temp.hitOccured) info = temp;
			}
		}
	//}
	//else cout << "null world pointer" << endl;
}