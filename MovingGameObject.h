// Represent a visible game object that has methods for moving around and
// collision detection.

#pragma once
#include "VisibleGameObject.h"
//#include "Game.h" // Cannot be included due to circular dependencies?

class MovingGameObject: public VisibleGameObject
{
public:
	MovingGameObject(void);
	virtual ~MovingGameObject(void); // Must be virtual!

	// Gets you a pointer to an array containing the velocity
	// TODO Why const?
	virtual float* GetVelocity() const;

protected:
	float _velocityX;
	float _velocityY;
	float _maxVelocity;

	float _movedLeft;
	float _movedRight;
	float _movedUp;
	float _movedDown;

	// TODO Should these be virtual?
	// Sets the velocity to max velocity were it to exceed it
	virtual void LimitVelocity();
	// Make the object change direction upon hitting walls
	virtual void WallBounce();
	// Moves the sprite with the given delta
	virtual void MoveSprite(float elapsedTime);
	// Collision detection
	virtual void DetectCollision();
};
