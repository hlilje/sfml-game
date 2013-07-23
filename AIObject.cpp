#include "stdafx.h"
#include "AIObject.h"
#include "Game.h"
#include "Entity.h"

AIObject::AIObject()
{
	Load("img/object.png");
	assert(IsLoaded());

	// Set origin at center
	GetSprite().setOrigin(GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().width/2);

	//SetPosition(10.0f, 10.0f);

	// Inherited from base class
	_velocityX = 10.0f;
	_velocityY = 10.0f;
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
		float w = GetWidth();
		float h = GetHeight();

		float moveByX = _velocityX * elapsedTime;
		float moveByY = _velocityY * elapsedTime;

		sf::Sprite sprite = GetSprite();

		if(playerPos.x - pos.x + moveByX < playerPos.x - pos.x)
			sprite.move(moveByX, 0.0f);
		else
			sprite.move(- moveByX, 0.0f);
			std::cout << moveByX << "\n";
			std::cout << "AIObject: move negative X\n";
		if(playerPos.y - pos.y + moveByY < playerPos.y - pos.y)
			sprite.move(0.0f, moveByY);
		else
			sprite.move(0.0f, - moveByY);
			std::cout << "AIObject: move negative Y\n";

		// Inherited from base class
		LimitVelocity();
		WallBounce();
		//MoveSprite(elapsedTime);
	}
}
