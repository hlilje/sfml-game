#include "stdafx.hpp"
#include "moving_game_object.hpp"
#include "game.hpp"


MovingGameObject::MovingGameObject(const float velocity_x, const float velocity_y, const float max_velocity) :
    _velocity_x(velocity_x),
    _velocity_y(velocity_y),
    _max_velocity(max_velocity),
    _moved_left(false),
    _moved_right(false),
    _moved_up(false),
    _moved_down(false) { }

void MovingGameObject::LimitVelocity() {
    if (_velocity_x > _max_velocity)
        _velocity_x = _max_velocity;
    else if (_velocity_x < - _max_velocity)
        _velocity_x = - _max_velocity;
    if (_velocity_y > _max_velocity)
        _velocity_y = _max_velocity;
    else if (_velocity_y < - _max_velocity)
        _velocity_y = - _max_velocity;
}

void MovingGameObject::WallBounce() {
    const sf::Vector2f pos = GetPosition();
    const float        w   = GetWidth();
    const float        h   = GetHeight();

    const float x_check = pos.x + w / 2;
    const float y_check = pos.y + h / 2;

    // Bounce at edges of screen and compensate if it escapes it
    if (x_check < w) {
        _velocity_x = _velocity_x * -1.0f;
        SetPosition(w / 2, pos.y);
    } else if (x_check > Game::SCREEN_WIDTH) {
        _velocity_x = _velocity_x * -1.0f;
        SetPosition(Game::SCREEN_WIDTH - w / 2, pos.y);
    }
    if (y_check < h) {
        _velocity_y = _velocity_y * -1.0f;
        SetPosition(pos.x, h / 2);
    } else if (y_check > Game::SCREEN_HEIGHT) {
        _velocity_y = _velocity_y * -1.0f;
        SetPosition(pos.x, Game::SCREEN_HEIGHT - h / 2);
    }
}

std::pair<float, float> MovingGameObject::GetVelocity() const {
    return std::pair<float, float>(_velocity_x, _velocity_y);
}

void MovingGameObject::MoveSprite(const float elapsed_time) {
    float moveByX = _velocity_x * elapsed_time;
    float moveByY = _velocity_y * elapsed_time;

    if (_velocity_x < 0) {
        _moved_left = true;
        _moved_right = false;
    } else if (_velocity_x > 0) {
        _moved_left = false;
        _moved_right = true;
    } else if (_velocity_x == 0) {
        _moved_left = false;
        _moved_right = false;
    }
    if (_velocity_y < 0) {
        _moved_up = true;
        _moved_down = false;
    } else if (_velocity_y > 0) {
        _moved_up = false;
        _moved_down = true;
    } else if (_velocity_y == 0) {
        _moved_up = false;
        _moved_down = false;
    }

    this->GetSprite().move(moveByX, moveByY);
}

void MovingGameObject::HandleMovingCollisions() {
    auto it = _collides_with.begin();
    while (it != _collides_with.end()) {
        if ((*it)->IsNoClip()) {
            RemoveCollidingObject(*it++);
            continue;
        }
        // Coordinate info needed to be able to reset the object when
        // it overlaps the other
        sf::Vector2f coll_pos = (*it)->GetPosition();
        sf::Vector2f this_pos = GetPosition();

        sf::Rect<float> coll_rect = (*it)->GetBoundingRect();
        sf::Rect<float> this_rect = GetBoundingRect();

        const float coll_r_side = coll_rect.left + coll_rect.width;
        const float coll_l_side = coll_rect.left;
        const float coll_u_side = coll_rect.top;
        const float coll_d_side = coll_rect.top + coll_rect.height;

        const float this_r_side = this_rect.left + this_rect.width;
        const float this_l_side = this_rect.left;
        const float this_u_side = this_rect.top;
        const float this_d_side = this_rect.top + this_rect.height;

        // Flip direction upon collision
        if (_moved_left) {
            _velocity_x = - _velocity_x;
            //if(this_l_side < coll_r_side)
            //    SetPosition(thisPos.x + (coll_r_side - this_l_side), thisPos.y);
        } else if (_moved_right) {
            _velocity_x = - _velocity_x;
            //if(this_r_side > coll_l_side)
            //    SetPosition(thisPos.x - (this_r_side - coll_l_side), thisPos.y);
        }
        if (_moved_up) {
            _velocity_y = - _velocity_y;
            //if(this_d_side > coll_u_side)
            //    SetPosition(thisPos.x, thisPos.y - (this_d_side - coll_u_side));
        } else if (_moved_down) {
            _velocity_y = - _velocity_y;
            //if(this_u_side < coll_d_side)
            //    SetPosition(thisPos.x, thisPos.y + (coll_d_side - this_u_side));
        }

        RemoveCollidingObject(*it++);
    }
}
