// Represents a level state in the game.

#pragma once

class Level
{
public:
    // Each enum identifies a level in the game
	enum LevelID { Level1 };  

	void Show(sf::RenderWindow& window);
	void Switch(LevelID lvl);
};
