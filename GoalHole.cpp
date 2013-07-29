#include "stdafx.h"
#include "GoalHole.h"
#include "Game.h"

GoalHole::GoalHole()
{
	Load("img/object.png");
	assert(IsLoaded());

	CenterOrigo();

	_startPosSet = false;
}

GoalHole::~GoalHole()
{
}

void GoalHole::Update(float elapsedTime)
{
	SetStartPos(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);

	PlayerObject* player = dynamic_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));

	if(player != NULL)
	{
		sf::Rect<float> playerRect = player->GetBoundingRect();
		if(playerRect.intersects(this->GetBoundingRect()))
			std::cout << "GoalHole intersects player\n";
	}
}
