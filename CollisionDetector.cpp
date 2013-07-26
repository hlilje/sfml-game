#include "stdafx.h"
#include "CollisionDetector.h"

CollisionDetector::CollisionDetector()
{	
}

CollisionDetector::~CollisionDetector()
{
}

// TODO
void CollisionDetector::AddVisibleObject(std::string name, VisibleGameObject* gameObject)
{
	_obsticles.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}
