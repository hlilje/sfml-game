// Represents a visible object that need to be drawn.

#pragma once

class VisibleGameObject
{
	// Virtual tells the compiler to look for a derivative when used on
	// a member function
public:
	VisibleGameObject(void);
	virtual ~VisibleGameObject(void);

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;

	virtual bool IsLoaded() const;
	// Returns a rectangle defining the size of the object, used for collision
	// detection.
	virtual sf::Rect<float> GetBoundingRect() const;

	// Add an object to the vector of objects currelty colliding with this
	virtual void AddCollidingObject(VisibleGameObject*);

protected:
	sf::Sprite& GetSprite();
	std::set<VisibleGameObject*> _collidesWith; // Holds all the objects currently colliding with this

	// Set new origin to center, default is top left
	virtual void CenterOrigo();

	// Delete a colliding object from the object set
	virtual void RemoveCollidingObject(VisibleGameObject*);

    // TODO Handle collisions relevant for a visual object
	virtual void HandleVisualCollisions();

    // True if this object is within the given tolerance of the given target position
	virtual bool VisibleGameObject::OnTarget(sf::Vector2f target, float tolerance);

private:
	// Could make this protected and remove GetSprite() for simplicity
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};
