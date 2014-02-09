#include "stdafx.h"
#include "GoalHole.h"
#include "Game.h"

GoalHole::GoalHole()
{
	Load("img/object.png");
	assert(IsLoaded());

	CenterOrigo();
	SetNoClip(true);
}

GoalHole::~GoalHole()
{
}

void GoalHole::Update(float elapsedTime)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));

	if (player != NULL)
	{
		if (OnTarget(player->GetPosition(), 10.0f))
		{
			std::cout << "WIN" << std::endl;
		}
	}

	HandleVisualCollisions();
}
