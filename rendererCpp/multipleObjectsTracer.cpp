#include "stdafx.h"
#include "multipleObjectsTracer.h"
#include "material.h"

vector3 multipleObjectsTracer::traceRay(rayHitInfo &info)
{
	//info to informacja o najbli¿szym przeciêciu, temp to informacja o przeciêziu w aktualej iteracji pêtli
	rayHitInfo temp = info; 
	if (info.worldToRender) {
		for (geometricObject *currentObject : info.worldToRender->objectsInTheScene) {
			currentObject->hit(temp);
			//zmieniamy info na temp jeœli nie by³o jeszcze trafienia lub trafienie by³o dalej od kamery
			if (temp.hitOccured && (!info.hitOccured || temp.t < info.t)) {
				info = temp;
			}
		}
	}
	else cout << "null world pointer" << endl;

	if (info.materialToShade) return info.materialToShade->shade(info);
	else return vector3(0, 0, 0);
}

void multipleObjectsTracer::traceShadowRay(rayHitInfo & info, light *lightToUse)
{
	int size = info.worldToRender->objectsInTheScene.size();
	
	//funkcje hit ustawiaj¹ info o przeciêciu tylko jeœli jest trafienie
	rayHitInfo temp = info;
	if (info.worldToRender) {
		//if a light is a point light, we check if there was a hit between light origin and shaded point
		if (lightToUse->isPointLight) {
			float distanceToLightSource = (lightToUse->origin - info.incomingRay.origin).x / info.incomingRay.direction.x;
			//wychodzimy z pêtli od tazu kiedy by³o przeciêcie, nie trzeba sprawdzaæ innych obiektów
			for (int i = 0; i < size; ++i) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				//we change info only if hit in temp is between light source and shadow ray origin
				if (temp.hitOccured && temp.t < distanceToLightSource){
					info = temp;
					return;
				}
			}
		}
		//if a light is a directional light we check if there is any hit starting from shaded point in inverse direction of light
		else {
			//wychodzimy z pêtli od razu kiedy by³o przeciêcie, nie trzeba sprawdzaæ innych obiektów
			for (int i = 0; i < size; ++i) {
				info.worldToRender->objectsInTheScene[i]->hit(temp);
				if (temp.hitOccured) {
					info = temp;
					return;
				}
			}
		}
	}
	else cout << "null world pointer" << endl;
}
