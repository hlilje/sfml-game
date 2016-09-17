#include "stdafx.hpp"
#include "entity.hpp"
#include "game.hpp"


Entity::Entity() :
    MovingGameObject(400.0f, 400.0f, 400.0f),
    _time_since_start(0.0f) {
    Load("img/entity.png");
    assert(IsLoaded());

    CenterOrigo();
    SetNoClip(false);
}

void Entity::Update(const float elapsed_time) {
    _time_since_start += elapsed_time;

    const PlayerObject * const player = dynamic_cast<PlayerObject *>(Game::GetGameObjectManager().Get(GameObject::Player));
    const AIObject * const     ai     = dynamic_cast<AIObject *>(Game::GetGameObjectManager().Get(GameObject::AI));

    if (player) {
        // TODO
    }

    LimitVelocity();
    WallBounce();
    HandleMovingCollisions();
    MoveSprite(elapsed_time);
}
