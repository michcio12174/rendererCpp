#include "stdafx.h"
#include "rectangle.h"

//pierwszy z 3 punktów zostanie zapamiêtany w plane jako point
rectangle::rectangle(vector3 leftUpperCorner, float width, float height, material * materialToUse) :
	plane(leftUpperCorner, leftUpperCorner - vector3(1, 0, 0, false), leftUpperCorner - vector3(1, 1, 0, false), materialToUse)
{
	this->width = width;
	this->height = height;
}

bool rectangle::hit(rayHitInfo & info)
{
	plane::hit(info);
	if (info.hitOccured) {
		if (info.hitPoint.x >= A.position.x &&
			info.hitPoint.x < A.position.x + width &&
			info.hitPoint.y < A.position.y &&
			info.hitPoint.y >= A.position.y - height)
		{
			vector3 point1(info.hitPoint.x, A.position.y, A.position.z, false),
				point2(A.position.x, info.hitPoint.y, A.position.z, false);
			
			info.hitPoint.x = (A.position - point1).length() / width;
			info.hitPoint.y = (A.position - point2).length() / height;

			return true;
		}
		else {
			info.hitOccured = false;
		}
	}

	return false;
}
