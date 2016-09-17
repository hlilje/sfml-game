#pragma once

#include "ai_object.hpp"
#include "entity.hpp"
#include "game_object_manager.hpp"
#include "goal_hole.hpp"
#include "level.hpp"
#include "intent_manager.hpp"
#include "obstacle.hpp"
#include "player_object.hpp"


class Game {
private:
    enum GameState {
        Exiting,
        Paused,
        Playing,
        ShowingMenu,
        ShowingSplash,
        ShowingWin,
        Uninitialized
    };

    static sf::RenderWindow  _main_window;
    static GameObjectManager _game_object_manager;
    static IntentManager     _intent_manager;
    static GameState         _game_state;

public:
    static const unsigned int SCREEN_WIDTH  = 1024;
    static const unsigned int SCREEN_HEIGHT = 768;

private:
    static void GameLoop();
    static bool IsExiting();
    static void ShowSplashScreen();
    static void ShowMenu();
    static void ShowWinScreen();

public:
    static void Start();
    static const sf::RenderWindow &  GetWindow();
    static sf::Event                 GetInput();
    static const GameObjectManager & GetGameObjectManager();
};
