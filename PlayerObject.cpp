#include "stdafx.h"
#include "PlayerObject.h"
#include "Game.h"

PlayerObject::PlayerObject()
{
	// Since these will never change, load them here
	Load("img/object.png");
	assert(IsLoaded()); // Can't return false in constructor

	// Set new origin to center, default is top left
	GetSprite().setOrigin(GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/2);
	//SetPosition(200, 200); // Doesn't work
	std::cout << "PlayerObject ctor\n";

	// Inherited
	_velocityX = 0.0f;
	_velocityY = 0.0f;
	_maxVelocity = 500.0f;
	_startPosSet = false;

	_movedLeft = false;
	_movedRight = false;
	_movedUp = false;
	_movedDown = false;
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

	float velocityInc = 10.0f; // Pixels

	// Use polling instead of event
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_velocityX -= velocityInc;
		_movedLeft = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_velocityX += velocityInc;
		_movedRight = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_velocityY -= velocityInc;
		_movedUp = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_velocityY += velocityInc;
		_movedDown = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_velocityX = 0.0f;
		_velocityY = 0.0f;
		_movedLeft = false;
		_movedRight = false;
		_movedUp = false;
		_movedDown = false;
	}

	// Protected inherited members of base class
	LimitVelocity();
	WallBounce();
	MoveSprite(elapsedTime);
}
