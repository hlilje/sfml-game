#include "stdafx.hpp"
#include "game.hpp"
#include "main_menu.hpp"
#include "service_locator.hpp"
#include "sound_provider.hpp"
#include "splash_screen.hpp"
#include "win_screen.hpp"

sf::RenderWindow  Game::_main_window;
GameObjectManager Game::_game_object_manager;
Game::GameState   Game::_game_state = Uninitialized;


void Game::Start() {
    if (_game_state != Uninitialized)
        return;

    _main_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFMLGame", sf::Style::Default);
    _main_window.setVerticalSyncEnabled(true);

    SoundProvider sound_provider;
    ServiceLocator::RegisterServiceLocator(&sound_provider);
    ServiceLocator::GetAudio()->PlaySong("audio/soundtrack.ogg", true);

    Level level;

    if (!level.Load(Level::Level1))
        _game_state = Game::Exiting;

    PlayerObject * const player     = new PlayerObject();
    AIObject * const     ai         = new AIObject();
    Entity * const       entity     = new Entity();
    GoalHole * const     goal_hole  = new GoalHole();
    Obstacle * const     obstacle_1 = new Obstacle();

    player->SetPosition(200.0f, 200.0f);
    ai->SetPosition(500.0f, 500.0f);
    entity->SetPosition(Game::SCREEN_WIDTH - 300.0f, 100.0f);
    goal_hole->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    obstacle_1->SetPosition(SCREEN_WIDTH / 2 + 300.0f, SCREEN_HEIGHT / 2 + 300.0f);

    _game_object_manager.Add(GameObject::Player, player);
    _game_object_manager.Add(GameObject::AI, ai);
    _game_object_manager.Add(GameObject::Entity, entity);
    _game_object_manager.Add(GameObject::GoalHole, goal_hole);
    _game_object_manager.Add(GameObject::Obstacle_1, obstacle_1);

    _game_state = Game::ShowingSplash;

    while (!IsExiting())
        GameLoop();

    _main_window.close();
}

void Game::GameLoop() {
    switch (_game_state) {
    case Game::ShowingMenu:
        ShowMenu();
        break;
    case Game::ShowingSplash:
        ShowSplashScreen();
        break;
    case Game::ShowingWin:
        ShowWinScreen();
        break;
    case Game::Playing:
        sf::Event current_event;

        _main_window.clear(sf::Color::Black);

        _game_object_manager.UpdateAll();
        _game_object_manager.CheckAllCollisions();
        _game_object_manager.DrawAll(_main_window);

        _main_window.display();

        while (_main_window.pollEvent(current_event)) {
            switch (current_event.type) {
            case sf::Event::Closed:
                _game_state = Game::Exiting;
                break;
            case sf::Event::KeyPressed:
                if (current_event.key.code == sf::Keyboard::Escape)
                    ShowMenu();
                break;
            default:
                break;
            }
        }
    }
}

bool Game::IsExiting() {
    return _game_state == Game::Exiting;
}

void Game::ShowSplashScreen() {
    SplashScreen splash_screen;
    splash_screen.Show(_main_window);
    _game_state = Game::ShowingMenu;
}

void Game::ShowMenu() {
    MainMenu main_menu;
    MainMenu::MenuResult result = main_menu.Show(_main_window);

    switch (result) {
    case MainMenu::Exit:
        _game_state = Game::Exiting;
        break;
    case MainMenu::Play:
        _game_state = Game::Playing;
        break;
    }
}

void Game::ShowWinScreen() {
    WinScreen win_screen;
    win_screen.Show(_main_window);
    _game_state = Game::ShowingMenu;
}

const sf::RenderWindow & Game::GetWindow() {
    return Game::_main_window;
}

const GameObjectManager & Game::GetGameObjectManager() {
    return Game::_game_object_manager;
}

sf::Event Game::GetInput() {
    sf::Event current_event;
    _main_window.pollEvent(current_event);
    return current_event;
}
