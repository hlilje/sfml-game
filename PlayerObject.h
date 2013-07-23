// Represents the player object in the game.

#pragma once
#include "MovingGameObject.h"

//class PlayerObject: public VisibleGameObject // Only derive public members
class PlayerObject: public MovingGameObject // Only derive protected members
{
public:
	PlayerObject(void);
	~PlayerObject(void);

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

private:

};
