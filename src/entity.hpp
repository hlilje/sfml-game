#pragma once

#include "moving_game_object.hpp"


class Entity: public MovingGameObject {
private:
    float _time_since_start;

public:
    Entity();

    void Update(const float elapsed_time);
};
