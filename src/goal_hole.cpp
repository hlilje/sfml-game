#include "stdafx.hpp"
#include "goal_hole.hpp"
#include "game.hpp"


GoalHole::GoalHole() {
    Load("img/object.png");
    assert(IsLoaded());

    CenterOrigo();
    SetNoClip(true);
}

void GoalHole::Update(const float elapsedTime) {
    const PlayerObject * const player = dynamic_cast<PlayerObject *>(Game::GetGameObjectManager().Get(GameObject::Player));

    if (player) {
        if (OnTarget(player->GetPosition(), 10.0f))
            std::cout << "WIN" << std::endl;
    }

    HandleVisualCollisions();
}
