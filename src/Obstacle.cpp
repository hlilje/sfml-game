#include "stdafx.h"
#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle()
{
	Load("img/object.png");
	assert(IsLoaded());

	CenterOrigo();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(float elapsedTime)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));

	if(player != NULL)
	{
        // TODO
	}

	HandleVisualCollisions(); // TODO
}
