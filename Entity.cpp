#include "stdafx.h"
#include "Entity.h"
#include "Game.h"
#include "ServiceLocator.h"

Entity::Entity():
	_elapsedTimeSinceStart(0.0f) // Time since entity was created
{
	Load("img/entity.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width/2, GetSprite().getLocalBounds().height/2);

	// Inherited
	_velocityX = 400.0f; // px/s
	_velocityY = 400.0f; // px/s
	_maxVelocity = 400.0f;
	_startPosSet = false;
}

Entity::~Entity()
{
}

void Entity::Update(float elapsedTime)
{
	SetStartPos(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
	_elapsedTimeSinceStart += elapsedTime;

	// Dynamic cast returns null if the object isn't capable of being casted to that type,
	// otherwise returns a pointer to the object.
	// Since Get() returns a VisibleGameObject pointer the cast is needed to get the members
	// of the inheriting class.
	// Overkill in this case since those methods aren't used.
	PlayerObject* player = dynamic_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));

	if(player != NULL) // Dangerous if null!
	{
		sf::Rect<float> playerRect = player->GetBoundingRect();
		if(playerRect.intersects(this->GetBoundingRect()))
			std::cout << "Entity intersects player\n";

		LimitVelocity();
		WallBounce();
		MoveSprite(elapsedTime);
	}
}
