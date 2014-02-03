// Represents a level state in the game. The levels themselves are hard coded
// to avoid modularity.

#pragma once
#include "Game.h"
#include "PlayerObject.h"

class Level
{
public:
	Level();
	~Level();

    // Each enum identifies a level in the game
	enum LevelID { Level1 };  

	bool Load(Level::LevelID lvl);
};
