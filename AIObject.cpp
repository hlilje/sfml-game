#include "stdafx.h"
#include "AIObject.h"
#include "Game.h"
#include "Entity.h"

AIObject::AIObject()
{
	Load("img/object.png");
	assert(IsLoaded());

	// Set origin at center
	GetSprite().setOrigin(GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/2);

	//SetPosition(10.0f, 10.0f);

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
		sf::Rect<float> playerRect = player->GetBoundingRect();
		if(playerRect.intersects(this->GetBoundingRect()))
			std::cout << "AIObject intersects player\n";

		sf::Vector2f pos = this->GetPosition();
		sf::Vector2f playerPos = player->GetPosition();

		float moveByX = _velocityX * elapsedTime;
		float moveByY = _velocityY * elapsedTime;

		float velocityInc = 9.0f;

		if(playerPos.x - pos.x < 0.0f)
		{
			//this->GetSprite().move(moveByX, 0.0f);
			_velocityX -= velocityInc;
		}
		else
		{
			//this->GetSprite().move(- moveByX, 0.0f);
			_velocityX += velocityInc;
		}
		if(abs(playerPos.x - pos.x) < 1.0f)
		{
			_velocityX = 0.0f;
		}
		if(playerPos.y - pos.y < 0.0f)
		{
			//this->GetSprite().move(0.0f, moveByY);
			_velocityY -= velocityInc;
		}
		else
		{
			//this->GetSprite().move(0.0f, - moveByY);
			_velocityY += velocityInc;
		}
		if(abs(playerPos.y - pos.y) < 1.0f)
		{
			_velocityY = 0.0f;
		}

		// Inherited from base class
		LimitVelocity();
		WallBounce();
		MoveSprite(elapsedTime);
	}
}
