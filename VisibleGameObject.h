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
	bool _startPosSet;
	sf::Sprite& GetSprite();
	std::set<VisibleGameObject*> _collidesWith; // Holds all the objects currently colliding with this

	// Set new origin to center, default is top left
	virtual void CenterOrigo();

	// Hack to get around the fact that you can't seem to just call SetPosition()
	// in the constructor, this method sets the flag _startPosSet to true after
	// setting the given coordinates.
	virtual void SetStartPos(float x, float y);

	// Delete a colliding object from the object set
	virtual void RemoveCollidingObject(VisibleGameObject*);

	// Currently not implemented, but handles collisions in a way which
	// makes sense for both moving and stationary objects
	virtual void HandleVisualCollisions();

private:
	// Could make this protected and remove GetSprite() for simplicity
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};
