#include "stdafx.h"
#include "AIObject.h"
#include "Game.h"
#include "Entity.h"

AIObject::AIObject()
{
	Load("img/object.png");
	assert(IsLoaded());

	CenterOrigo();

	// Inherited from base class
	_velocityX = 0.0f;
	_velocityY = 0.0f;
	_maxVelocity = 400.0f;
	_startPosSet = false;
}

AIObject::~AIObject()
{
}

void AIObject::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

void AIObject::Update(float elapsedTime)
{
	SetStartPos(500.0f, 500.0f);
	// Would be more efficient to store pointer then to retrieve it every frame
	const PlayerObject* player = static_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));

	if(player != NULL)
	{
		sf::Vector2f pos = this->GetPosition();
		sf::Vector2f playerPos = player->GetPosition();

		float velocityInc = 9.0f;

		if(playerPos.x - pos.x < 0.0f)
		{
			_velocityX -= velocityInc;
		}
		else
		{
			_velocityX += velocityInc;
		}
		if(playerPos.y - pos.y < 0.0f)
		{
			_velocityY -= velocityInc;
		}
		else
		{
			_velocityY += velocityInc;
		}

		// Inherited from base class
		LimitVelocity();
		WallBounce();
		HandleMovingCollisions();
		MoveSprite(elapsedTime);
	}
}
