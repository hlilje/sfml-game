// Static global interface, master game class.

#pragma once
#include "PlayerObject.h"
#include "AIObject.h"
#include "Entity.h"
#include "GameObjectManager.h"

// This class is entirely static, but a dynamic RenderWindow is created
// in GameLoop
class Game
{
public:
	// Global game variables
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	const static GameObjectManager& GetGameObjectManager();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	// The various states the game can be in
	enum GameState { Uninitialized, ShowingSplash, Paused, 
		ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
};
