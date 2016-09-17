#include "stdafx.hpp"
#include "ai_object.hpp"
#include "game.hpp"


AIObject::AIObject() :
    MovingGameObject(0.0f, 0.0f, 400.0f) {
    Load("img/object.png");
    assert(IsLoaded());

    CenterOrigo();
    SetNoClip(false);
}

void AIObject::Draw(sf::RenderWindow & render_window) {
    VisibleGameObject::Draw(render_window);
}

void AIObject::Update(const float elapsed_time) {
    // TODO: Store pointer instead of retrieving it?
    const PlayerObject * const player = static_cast<PlayerObject *>(Game::GetGameObjectManager().Get(GameObject::Player));

    if (player) {
        const sf::Vector2f pos = this->GetPosition();
        const sf::Vector2f player_pos = player->GetPosition();

        float velocity_inc = 9.0f;

        if (player_pos.x - pos.x < 0.0f)
            _velocity_x -= velocity_inc;
        else
            _velocity_x += velocity_inc;
        if (player_pos.y - pos.y < 0.0f)
            _velocity_y -= velocity_inc;
        else
            _velocity_y += velocity_inc;

        LimitVelocity();
        WallBounce();
        HandleMovingCollisions();
        MoveSprite(elapsed_time);
    }
}
