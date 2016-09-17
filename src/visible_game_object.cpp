#include "stdafx.hpp"
#include "visible_game_object.hpp"


VisibleGameObject::VisibleGameObject():
    _is_loaded(true) { }

void VisibleGameObject::Load(const std::string & filename) {
    if (!_texture.loadFromFile(filename)) {
        _filename = "";
        _is_loaded = false;
    } else {
        _filename = filename;
        _sprite.setTexture(_texture);
        _is_loaded = true;
    }
}

void VisibleGameObject::Draw(sf::RenderWindow & window) {
    if (_is_loaded)
        window.draw(_sprite);
}

// TODO Only for inheritance, not implemented here
void VisibleGameObject::Update(const float elapsed_time)
{
}

void VisibleGameObject::SetPosition(const float x, const float y) {
    if (_is_loaded)
        _sprite.setPosition(x, y);
}

void VisibleGameObject::CenterOrigo() {
    _sprite.setOrigin(_sprite.getLocalBounds().width / 2,
                      _sprite.getLocalBounds().height / 2);
}

sf::Vector2f VisibleGameObject::GetPosition() const {
    if (_is_loaded)
        return _sprite.getPosition();
    return sf::Vector2f();
}

sf::Sprite & VisibleGameObject::GetSprite() {
    return _sprite;
}

bool VisibleGameObject::IsLoaded() const {
    return _is_loaded;
}

float VisibleGameObject::GetHeight() const {
    return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const {
    return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const {
    return _sprite.getGlobalBounds();
}

void VisibleGameObject::AddCollidingObject(const VisibleGameObject * const object) {
    auto it = _collides_with.find(object);
    if (it == _collides_with.end())
        _collides_with.insert(object);
}

void VisibleGameObject::RemoveCollidingObject(const VisibleGameObject * const object) {
    auto it = _collides_with.find(object);
    if (it != _collides_with.end())
        _collides_with.erase(object);
}

void VisibleGameObject::HandleVisualCollisions() {
    auto it = _collides_with.begin();
    while (it != _collides_with.end())
        RemoveCollidingObject(*it++);
}

bool VisibleGameObject::OnTarget(const sf::Vector2f & target, const float tolerance) {
    float tol = tolerance;

    if (tol <= 0.0f)
        tol = 1.0f;

    const sf::Vector2f this_pos = GetPosition();

    if (std::abs(this_pos.x - target.x) < tol &&
        std::abs(this_pos.y - target.y) < tol)
        return true;

    return false;
}

bool VisibleGameObject::IsNoClip() const {
    return _no_clip;
}

void VisibleGameObject::SetNoClip(const bool no_clip) {
    _no_clip = no_clip;
}
