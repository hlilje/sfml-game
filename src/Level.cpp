#include "stdafx.h"
#include "Level.h"

Level::Level()
{	
}

Level::~Level()
{
}

bool Level::Load(Level::LevelID lvl)
{
	const PlayerObject* player = static_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));
	if (player == NULL)
		return false;

	switch (lvl)
	{
	case Level::Level1:
		return true;
	default:
		return false;
	}
}
