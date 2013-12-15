// Handles collision detection.

#pragma once
#include "VisibleGameObject.h"
#include "MovingGameObject.h"

class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);

	// Detects a collision between two given visible objects
	bool DetectCollision(VisibleGameObject*, VisibleGameObject*);

private:

};
