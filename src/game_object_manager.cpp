#include "stdafx.hpp"
#include "game_object_manager.hpp"


GameObjectManager::~GameObjectManager() {
    const auto deallocator = [](const std::pair<GameObject, VisibleGameObject *> & p) {
        delete p.second;
    };

    std::for_each(_game_objects.begin(), _game_objects.end(), deallocator);
}

void GameObjectManager::Add(const GameObject id,
                            VisibleGameObject * const game_object) {
    _game_objects.emplace(std::make_pair(id, game_object));
}

void GameObjectManager::Remove(const GameObject id) {
    auto results = _game_objects.find(id);
    if (results != _game_objects.end()) {
        delete results->second;
        _game_objects.erase(results);
    }
}

void GameObjectManager::RemoveAll() {
    for (auto it = _game_objects.begin(); it != _game_objects.end(); ++it) {
        delete it->second;
        _game_objects.erase(it);
    }
}

void GameObjectManager::DrawAll(sf::RenderWindow & window) const {
    for (const auto & pair : _game_objects)
        pair.second->Draw(window);
}

void GameObjectManager::UpdateAll() {
    const float time_delta = _clock.restart().asSeconds();

    for (const auto & pair : _game_objects)
        pair.second->Update(time_delta); // TODO: See where this was removed from
}

void GameObjectManager::CheckAllCollisions() const {
    for (const auto & pair1 : _game_objects) {
        VisibleGameObject * const obj1 = pair1.second;

        for (const auto & pair2 : _game_objects) {
            if (pair2.second == obj1)
                continue;

            VisibleGameObject * const obj2 = pair2.second;

            if (_detector.Collides(obj1, obj2)) {
                obj1->AddCollidingObject(obj2);
                obj2->AddCollidingObject(obj1);
            }
        }
    }
}

VisibleGameObject * GameObjectManager::Get(const GameObject id) const {
    auto results = _game_objects.find(id);
    if (results == _game_objects.end())
        return nullptr;
    return results->second;
}

int GameObjectManager::GetObjectCount() const {
    return _game_objects.size();
}
