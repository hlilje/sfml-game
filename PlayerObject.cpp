#include "stdafx.h"
#include "PlayerObject.h"
#include "Game.h"

PlayerObject::PlayerObject()
{
	// Since these will never change, load them here
	Load("img/object.png");
	assert(IsLoaded()); // Can't return false in constructor

	// Set new origin to center, default is top left
	GetSprite().setOrigin(GetSprite().getTextureRect().width/2, GetSprite().getTextureRect().height/2);
	SetPosition(200, 200); // Doesn't work
	std::cout << "PlayerObject ctor\n";

	// Inherited
	_velocityX = 0.0f;
	_velocityY = 0.0f;
	_maxVelocity = 400.0f;
	_startPosSet = false;
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

void PlayerObject::Update(float elapsedTime)
{
	SetStartPos(200.0f, 200.0f); // Inherited

	// Use polling instead of event
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_velocityX -= 10.0f; // Pixels
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_velocityX += 10.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_velocityY -= 10.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_velocityY += 10.0f;
	}

	// Protected inherited members of base class
	LimitVelocity();
	WallBounce();
	MoveSprite(elapsedTime);
}
