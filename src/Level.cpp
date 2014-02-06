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
	PlayerObject* player = static_cast<PlayerObject*>(Game::GetGameObjectManager().Get("Player"));
	AIObject* ai = static_cast<AIObject*>(Game::GetGameObjectManager().Get("AI"));
	Entity* entity = static_cast<Entity*>(Game::GetGameObjectManager().Get("Entity"));
	GoalHole* goalHole = static_cast<GoalHole*>(Game::GetGameObjectManager().Get("GoalHole"));
	Obstacle* obstacle1 = static_cast<Obstacle*>(Game::GetGameObjectManager().Get("Obstacle1"));
	if (player == NULL || ai == NULL  || entity == NULL || goalHole == NULL || obstacle1 == NULL)
        return false;

    int offset = 400;
	float w = 0.0f;
	float h = 0.0f;
	switch (lvl)
	{
	case Level::Level1:
		w = (float) ((std::rand() % (Game::SCREEN_WIDTH - offset)) + offset);
		h = (float) ((std::rand() % (Game::SCREEN_HEIGHT - offset)) + offset);
		player->SetPosition(w, h);
		w = (float) ((std::rand() % (Game::SCREEN_WIDTH - offset)) + offset);
		h = (float) ((std::rand() % (Game::SCREEN_HEIGHT - offset)) + offset);
        ai->SetPosition(w, h);
		w = (float) ((std::rand() % (Game::SCREEN_WIDTH - offset)) + offset);
		h = (float) ((std::rand() % (Game::SCREEN_HEIGHT - offset)) + offset);
		entity->SetPosition(w, h);
		w = (float) ((std::rand() % (Game::SCREEN_WIDTH - offset)) + offset);
		h = (float) ((std::rand() % (Game::SCREEN_HEIGHT - offset)) + offset);
		goalHole->SetPosition(w, h);
		w = (float) ((std::rand() % (Game::SCREEN_WIDTH - offset)) + offset);
		h = (float) ((std::rand() % (Game::SCREEN_HEIGHT - offset)) + offset);
		obstacle1->SetPosition(w, h);

		return true;
	default:
		return false;
	}
}
