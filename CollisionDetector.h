// Handles collision detection

#pragma once
#include "VisibleGameObject.h"
#include "MovingGameObject.h"

class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);

	void AddVisibleObject(std::string, VisibleGameObject*);
	void AddMovingObject(std::string, MovingGameObject*);
	void DetectCollision();

private:
	// Map holding every object to perform collision detection on
	std::map<std::string, VisibleGameObject*> _obsticles;
};
