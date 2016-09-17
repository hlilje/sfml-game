#pragma once


class VisibleGameObject {
private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string _filename;
    bool _is_loaded;
    bool _no_clip;

protected:
    std::unordered_set<const VisibleGameObject *> _collides_with;

protected:
    sf::Sprite & GetSprite();
    virtual void CenterOrigo();
    virtual void RemoveCollidingObject(const VisibleGameObject * const object);
    virtual void HandleVisualCollisions();
    virtual bool VisibleGameObject::OnTarget(const sf::Vector2f & target, const float tolerance);

public:
    VisibleGameObject();

    virtual void Load(const std::string & filename);
    virtual void Draw(sf::RenderWindow & window);
    virtual void Update(const float elapsed_time);

    virtual void SetPosition(const float x, const float y);
    virtual sf::Vector2f GetPosition() const;
    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual bool IsLoaded() const;
    virtual bool IsNoClip() const;
    virtual void SetNoClip(const bool no_clip);
    virtual sf::Rect<float> GetBoundingRect() const;

    virtual void AddCollidingObject(const VisibleGameObject * const object);
};
