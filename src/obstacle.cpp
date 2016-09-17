#include "stdafx.hpp"
#include "obstacle.hpp"
#include "game.hpp"


Obstacle::Obstacle() {
    Load("img/object.png");
    assert(IsLoaded());

    CenterOrigo();
    SetNoClip(false);
}

void Obstacle::Update(const float elapsed_time) {
    const PlayerObject * const player = dynamic_cast<PlayerObject *>(Game::GetGameObjectManager().Get(GameObject::Player));

    if (player) {
        // TODO
    }

    HandleVisualCollisions();
}
