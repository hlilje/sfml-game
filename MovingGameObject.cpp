#include "stdafx.h"
#include "MovingGameObject.h"
#include "Game.h" // Cannot be included in header due to circular dependencies?

MovingGameObject::MovingGameObject()
{
}

MovingGameObject::~MovingGameObject()
{
}

void MovingGameObject::LimitVelocity()
{
	if(_velocityX > _maxVelocity)
		_velocityX = _maxVelocity;
	if(_velocityY > _maxVelocity)
		_velocityY = _maxVelocity;
}

void MovingGameObject::WallBounce()
{
	sf::Vector2f pos = this->GetPosition();
	float w = GetWidth();
	float h = GetHeight();

	// Bounce at edges of screen and compensate if it escapes it
	if((pos.x+w/2) < w)
	{
		_velocityX = _velocityX * -1.0f;
		this->SetPosition(w/2, pos.y);
	}
	else if((pos.x+w/2) > Game::SCREEN_WIDTH)
	{
		_velocityX = _velocityX * -1.0f;
		this->SetPosition(Game::SCREEN_WIDTH-w/2, pos.y);
	}
	if((pos.y+h/2) < h)
	{
		_velocityY = _velocityY * -1.0f;
		this->SetPosition(pos.x, h/2);
	}
	else if((pos.y+h/2) > Game::SCREEN_HEIGHT)
	{
		_velocityY = _velocityY * -1.0f;
		this->SetPosition(pos.x, Game::SCREEN_HEIGHT-h/2);
	}
}

float* MovingGameObject::GetVelocity() const
{
	float velocity[2] = {_velocityX, _velocityY};
	return velocity;
}
