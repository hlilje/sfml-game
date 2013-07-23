// Represents an unidentified entity in the game.

#pragma once
#include "MovingGameObject.h"

class Entity: public MovingGameObject
{
public:
	Entity(void);
	~Entity(void);

	void Update(float); // Override it and implement it again

private:
	float _elapsedTimeSinceStart; // Delay timer
};
