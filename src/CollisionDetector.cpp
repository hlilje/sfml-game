#include "stdafx.h"
#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{	
}

CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::DetectCollision(VisibleGameObject* obj1, VisibleGameObject* obj2)
{
	bool collides = false;

	if(obj1->GetBoundingRect().intersects(obj2->GetBoundingRect()))
	{
		collides = true;
	}

	return collides;
}
