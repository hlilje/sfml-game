// Class representing an obstacle in the game.

#pragma once
#include "VisibleGameObject.h"

class Obstacle: public VisibleGameObject
{
public:
	Obstacle(void);
	~Obstacle(void);

	void Update(float);

private:

};
