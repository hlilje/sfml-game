#pragma once

#include "collision_detector.hpp"
#include "constants.hpp"
#include "visible_game_object.hpp"


class GameObjectManager {
private:
    std::unordered_map<GameObject,
                       VisibleGameObject *> _game_objects;
    sf::Clock                               _clock;
    const CollisionDetector                 _detector;

public:
    ~GameObjectManager();

    void Add(const GameObject id, VisibleGameObject * const game_object);
    void Remove(const GameObject id);
    void RemoveAll();
    void DrawAll(sf::RenderWindow & window) const;
    void UpdateAll();
    void CheckAllCollisions() const;
    VisibleGameObject * Get(const GameObject id) const;
    int GetObjectCount() const;
};
