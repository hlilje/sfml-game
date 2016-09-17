#pragma once

#include "visible_game_object.hpp"


class MovingGameObject: public VisibleGameObject {
protected:
    float _velocity_x;
    float _velocity_y;
    float _max_velocity;

    float _moved_left;
    float _moved_right;
    float _moved_up;
    float _moved_down;

public:
    virtual std::pair<float, float> GetVelocity() const;

protected:
    MovingGameObject(const float velocity_x, const float velocity_y, const float max_velocity);

    virtual void LimitVelocity();
    virtual void WallBounce();
    virtual void MoveSprite(const float elapsed_time);
    virtual void HandleMovingCollisions();
};
