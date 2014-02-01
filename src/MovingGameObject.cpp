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
	else if(_velocityX < - _maxVelocity)
		_velocityX = - _maxVelocity;
	if(_velocityY > _maxVelocity)
		_velocityY = _maxVelocity;
	else if(_velocityY < - _maxVelocity)
		_velocityY = - _maxVelocity;
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

void MovingGameObject::MoveSprite(float elapsedTime)
{
	float moveByX = _velocityX * elapsedTime;
	float moveByY = _velocityY * elapsedTime;

	// Set movement flags
	if(_velocityX < 0)
	{
		_movedLeft = true;
		_movedRight = false;
	}
	else if(_velocityX > 0)
	{
		_movedLeft = false;
		_movedRight = true;
	}
	else if(_velocityX == 0)
	{
		_movedLeft = false;
		_movedRight = false;
	}
	if(_velocityY < 0)
	{
		_movedUp = true;
		_movedDown = false;
	}
	else if(_velocityY > 0)
	{
		_movedUp = false;
		_movedDown = true;
	}
	else if(_velocityY == 0)
	{
		_movedUp = false;
		_movedDown = false;
	}

	// fps = 1 / delta
	this->GetSprite().move(moveByX, moveByY);
}

void MovingGameObject::HandleMovingCollisions()
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.begin();
	while(it != _collidesWith.end())
	{
		// Coordinate info needed to be able to reset the object when
		// it overlaps the other
		sf::Vector2f collPos = (*it)->GetPosition();
		sf::Vector2f thisPos = GetPosition();

		sf::Rect<float> collRect = (*it)->GetBoundingRect();
		sf::Rect<float> thisRect = GetBoundingRect();

		float collRSide = collRect.left + collRect.width;
		float collLSide = collRect.left;
		float collUSide = collRect.top;
		float collDSide = collRect.top + collRect.height;

		float thisRSide = thisRect.left + thisRect.width;
		float thisLSide = thisRect.left;
		float thisUSide = thisRect.top;
		float thisDSide = thisRect.top + thisRect.height;

		// Flip direction upon collision
		if(_movedLeft)
		{
			_velocityX = - _velocityX;
			//if(thisLSide < collRSide)
			//	SetPosition(thisPos.x + (collRSide - thisLSide), thisPos.y);
		}
		else if(_movedRight)
		{
			_velocityX = - _velocityX;
			//if(thisRSide > collLSide)
			//	SetPosition(thisPos.x - (thisRSide - collLSide), thisPos.y);
		}
		if(_movedUp)
		{
			_velocityY = - _velocityY;
			//if(thisDSide > collUSide)
			//	SetPosition(thisPos.x, thisPos.y - (thisDSide - collUSide));
		}
		else if(_movedDown)
		{
			_velocityY = - _velocityY;
			//if(thisUSide < collDSide)
			//	SetPosition(thisPos.x, thisPos.y + (collDSide - thisUSide));
		}

		// The increment returns the previous value, which is the one to delete
		RemoveCollidingObject(*it++);
	}
}
