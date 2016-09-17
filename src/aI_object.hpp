#pragma once

#include "moving_game_object.hpp"


class AIObject: public MovingGameObject {
public:
    AIObject();

    void Update(const float elapsed_time);
    void Draw(sf::RenderWindow & window);
};
