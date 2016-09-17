#include "stdafx.hpp"
#include "collision_detector.hpp"


bool CollisionDetector::Collides(const VisibleGameObject * const object1,
                                 const VisibleGameObject * const object2) const {
    return object1->GetBoundingRect().intersects(object2->GetBoundingRect());
}
