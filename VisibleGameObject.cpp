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
	//std::cout << "SetPosition\n"; // DEBUG

	if(_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
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

void VisibleGameObject::SetStartPos(float x, float y)
{
	if(!_startPosSet)
	{
		SetPosition(x, y);
		_startPosSet = true;
	}
}

void VisibleGameObject::AddCollidingObject(VisibleGameObject* obj)
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.find(obj);
	if(it == _collidesWith.end()) // Returns end if no match is found
	{
		std::cout << "AddCollidingObject: INSERT\n"; // DEBUG
		_collidesWith.insert(obj);
	}
}

void VisibleGameObject::RemoveCollidingObject(VisibleGameObject* obj)
{
	std::set<VisibleGameObject*>::iterator it = _collidesWith.find(obj);
	if(it != _collidesWith.end()) // Returns end if no match is found
	{
		std::cout << "AddCollidingObject: REMOVE\n"; // DEBUG
		_collidesWith.erase(obj);
	}
}

void VisibleGameObject::HandleVisualCollisions()
{
	// TODO Not implemented
}
