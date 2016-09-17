#include "stdafx.hpp"
#include "player_object.hpp"


PlayerObject::PlayerObject() :
    MovingGameObject(0.0f, 0.0f, 500.0f) {
    // Since these will never change, load them here
    Load("img/object.png");
    assert(IsLoaded());

    CenterOrigo();
    SetNoClip(false);
}

void PlayerObject::Draw(sf::RenderWindow & window) {
    VisibleGameObject::Draw(window);
}

void PlayerObject::Update(const float elapsed_time) {
    const float velocity_inc = 10.0f;

    // Use polling over events
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _velocity_x -= velocity_inc;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _velocity_x += velocity_inc;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        _velocity_y -= velocity_inc;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        _velocity_y += velocity_inc;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        _velocity_x = 0.0f;
        _velocity_y = 0.0f;
    }

    LimitVelocity();
    WallBounce();
    HandleMovingCollisions();
    MoveSprite(elapsed_time);
}
