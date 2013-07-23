// Represents an AI in the game.

#pragma once
#include "MovingGameObject.h"

//class AIObject: public VisibleGameObject
class AIObject: public MovingGameObject
{
public:
	AIObject(void);
	~AIObject(void);

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:

};
