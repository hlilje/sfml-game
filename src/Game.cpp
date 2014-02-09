#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "WinScreen.h"
#include "SoundProvider.h"
#include "ServiceLocator.h"

// Must be instanced manually due to being static.
// C++ requires them to be instantiated in the global namespace.
Game::GameState Game::_gameState = Uninitialized; // Since it has no constructor
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;

// Start function, never call this more than once
void Game::Start(void)
{
	// Check to make sure we only call this function once
	// No error is generated since the game exits immidiately
	if(_gameState != Uninitialized)
		return;

	// Init RenderWindow, the same as calling create?
	// Params: inner res + colour, title, optional style, optional OpenGL options
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFMLGame", sf::Style::Default);
	_mainWindow.setVerticalSyncEnabled(true);

	SoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);
	ServiceLocator::GetAudio()->PlaySong("audio/soundtrack.ogg", true);
	Level level;

	// Set start positions
	PlayerObject *player = new PlayerObject();
	player->SetPosition(200.0f, 200.0f);

	AIObject *ai = new AIObject();
	ai->SetPosition(500.0f, 500.0f);

	Entity *entity = new Entity();
	entity->SetPosition(Game::SCREEN_WIDTH - 300.0f, 100.0f);

	GoalHole *goalHole = new GoalHole();
	goalHole->SetPosition((SCREEN_WIDTH/2), (SCREEN_HEIGHT/2));

	Obstacle *obstacle1 = new Obstacle();
	obstacle1->SetPosition((SCREEN_WIDTH/2) + 300.0f, (SCREEN_HEIGHT/2) + 300.0f);

	_gameObjectManager.Add("Player", player);
	_gameObjectManager.Add("AI", ai);
	_gameObjectManager.Add("Entity", entity);
	_gameObjectManager.Add("GoalHole", goalHole);
	_gameObjectManager.Add("Obstacle1", obstacle1);

	if (!level.Load(Level::Level1)) // Abort if level load fails
		_gameState = Game::Exiting;

	_gameState = Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

// Check if the game is in the exiting state.
bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

// Main game loop.
void Game::GameLoop()
{
	// The game is only ever in one single state at a time
	switch(_gameState)
	{
	case Game::ShowingMenu:
		ShowMenu();
		break;
	case Game::ShowingSplash:
		ShowSplashScreen();
		break;
	case Game::Playing:
		// Check all events triggered since last iteration of the loop
		// Returns true if there is one and assigns it to currentEvent
		// Called in a while loop to iterate through the event queue
		sf::Event currentEvent;

		// The only good way to draw things is this cycle
		_mainWindow.clear(sf::Color::Black); // Must be called before drawing

		_gameObjectManager.UpdateAll();
		_gameObjectManager.CheckAllCollisions();
		_gameObjectManager.DrawAll(_mainWindow);

		_mainWindow.display(); // End the current frame

		while(_mainWindow.pollEvent(currentEvent))
		{
			switch (currentEvent.type)
			{
			case sf::Event::Closed:
				_gameState = Game::Exiting;
				break;
			case sf::Event::KeyPressed:
				if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
				break;
			default: // Don't handle other type of events
				break;
			}
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowWinScreen()
{
	WinScreen winScreen;
	winScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

// Handles progression between states
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

const sf::Event& Game::GetInput() 
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}
