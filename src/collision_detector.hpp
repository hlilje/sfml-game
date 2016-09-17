#pragma once

#include "visible_game_object.hpp"


class CollisionDetector {
public:
    bool Collides(const VisibleGameObject * const object1,
                  const VisibleGameObject * const object2) const;
};
