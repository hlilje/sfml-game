#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject():
	_isLoaded(true) // Called before this constructor without assignment
{

}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if(_texture.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow& renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

// Only for inheritance, not implemented here
void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if(_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::CenterOrigo()
{
	_sprite.setOrigin(_sprite.getLocalBounds().width/2,
		_sprite.getLocalBounds().height/2);
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

void VisibleGameObject::AddCollidingObject(VisibleGameObject* obj)
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.find(obj);
	if(it == _collidesWith.end()) // Returns end if no match is found
	{
		_collidesWith.insert(obj);
	}
}

void VisibleGameObject::RemoveCollidingObject(VisibleGameObject* obj)
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.find(obj);
	if(it != _collidesWith.end())
	{
		_collidesWith.erase(obj);
	}
}

void VisibleGameObject::HandleVisualCollisions()
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.begin();
	while(it != _collidesWith.end())
	{
		RemoveCollidingObject(*it++);
	}
}

bool VisibleGameObject::OnTarget(sf::Vector2f target, float tolerance)
{
	if (tolerance <= 0.0f) { tolerance = 1.0f; }
	sf::Vector2f thisPos = GetPosition();

	if (abs(thisPos.x - target.x) < tolerance && abs(thisPos.y - target.y) < tolerance)
	{
		return true;
	}

	return false;
}
