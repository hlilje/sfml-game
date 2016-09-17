#pragma once

#include "visible_game_object.hpp"


class GoalHole: public VisibleGameObject {
public:
    GoalHole();

    void Update(const float elapsed_time);
};