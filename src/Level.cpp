#include "stdafx.hpp"
#include "level.hpp"
#include "game.hpp"


bool Level::Load(const Level::LevelID level) {
    PlayerObject * const player = static_cast<PlayerObject *>(Game::GetGameObjectManager().Get(GameObject::Player));
    AIObject * const ai         = static_cast<AIObject *>(Game::GetGameObjectManager().Get(GameObject::AI));
    Entity * const entity       = static_cast<Entity *>(Game::GetGameObjectManager().Get(GameObject::Entity));
    GoalHole * const goal_hole  = static_cast<GoalHole *>(Game::GetGameObjectManager().Get(GameObject::GoalHole));
    Obstacle * const obstacle1  = static_cast<Obstacle *>(Game::GetGameObjectManager().Get(GameObject::Obstacle_1));
    if (!(player && ai && entity && goal_hole && obstacle1))
        return false;

    int offset = 400;
    int mod_w  = Game::SCREEN_WIDTH - offset;
    int mod_h  = Game::SCREEN_HEIGHT - offset;
    float w    = 0.0f;
    float h    = 0.0f;

    switch (level) {
    case Level::Level1:
        w = (float) ((std::rand() % mod_w) + offset);
        h = (float) ((std::rand() % mod_h) + offset);
        player->SetPosition(w, h);
        w = (float) ((std::rand() % mod_w) + offset);
        h = (float) ((std::rand() % mod_h) + offset);
        ai->SetPosition(w, h);
        w = (float) ((std::rand() % mod_w) + offset);
        h = (float) ((std::rand() % mod_h) + offset);
        entity->SetPosition(w, h);
        w = (float) ((std::rand() % mod_w) + offset);
        h = (float) ((std::rand() % mod_h) + offset);
        goal_hole->SetPosition(w, h);
        w = (float) ((std::rand() % mod_w) + offset);
        h = (float) ((std::rand() % mod_h) + offset);
        obstacle1->SetPosition(w, h);

        return true;
    }

    return false;
}
