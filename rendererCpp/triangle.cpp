#include "stdafx.h"
#include "triangle.h"

bool triangle::hit(rayHitInfo &info)
{
	//sprawdzam czy promieñ przecina p³aszczyznê, na której le¿y trójk¹t
	if (plane::hit(info))
	{
		//plane ustawi³a, ¿e by³o z ni¹ przeciêcie, ale to nie znaczy, ¿e przeciêliœmy trójk¹t
		info.hitOccured = false;

		//obliczam wektory miêdzy punktem przeciêcia i wierzcho³kami trójk¹ta
		vector3 DA = A.position - info.hitPoint;
		vector3 DB = B.position - info.hitPoint;
		vector3 DC = C.position - info.hitPoint;

		//sprawdzam ze zwyk³¹ normalk¹
		//cross = u*v*sin(k¹t)
		//jeœli k¹t < 180 stopni wychodzi wektor równoleg³y do normalnego
		//jeœli k¹t > 180 wychodzi wektor przeciwny, bo sin < 0
		//dot = |u|*|v|*cos(k¹t)
		//jeœli równoleg³e wychodzi cos = 1 > 0
		//jeœli k¹t 180, to wychodzi cos = -1 < 0
		//jeœli wszystkie dot dodatnie,to znaczy, ¿e k¹ty miêdzy wektorami
		//DA, DB, DC s¹ mniejsze od 180, czyli D jest w œrodku trójk¹ta
		if ((DA.cross(DB)).dot(normal) >= info.minIntersectionDistance &&
			(DB.cross(DC)).dot(normal) >= info.minIntersectionDistance &&
			(DC.cross(DA)).dot(normal) >= info.minIntersectionDistance)
			info.hitOccured = true;

		//i z odwrócon¹ normalk¹
		if ((DA.cross(DB)).dot(-normal) >= info.minIntersectionDistance &&
			(DB.cross(DC)).dot(-normal) >= info.minIntersectionDistance &&
			(DC.cross(DA)).dot(-normal) >= info.minIntersectionDistance)
			info.hitOccured = true;
	}
	return false;
}
