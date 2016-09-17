#pragma once

#include "moving_game_object.hpp"


class PlayerObject: public MovingGameObject {
public:
    PlayerObject();

    void Update(const float elapsed_time);
    void Draw(sf::RenderWindow & window);
};
