#pragma once

#include "visible_game_object.hpp"


class Obstacle: public VisibleGameObject {
public:
    Obstacle();

    void Update(const float elapsed_time);
};
