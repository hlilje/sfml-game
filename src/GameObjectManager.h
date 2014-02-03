// Master class to be able to easily manage all the game objects.
// This class handles the entire life cycle of pointers, and thus should they never
// be deleted outside of it.

#pragma once
#include "VisibleGameObject.h"
#include "MovingGameObject.h"
#include "CollisionDetector.h"

class GameObjectManager
{
public:
	// Might as well create these since the compiler always does anyways
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	void RemoveAll();
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

	// Uses CollisionDetector to decide if a collision happened and updates
	// each object's collision map
	void CheckAllCollisions();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	sf::Clock _clock;
	CollisionDetector* _collDect;

	// A functor, an object that can be called like a function
	// Overloads function operator ()
	// A class type functor
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};
