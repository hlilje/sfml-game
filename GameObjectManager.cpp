#include "stdafx.h"
#include "Game.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{	
	_collDect = new CollisionDetector();
}

GameObjectManager::~GameObjectManager()
{
	// Takes two iterators and a unary operator
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
	delete _collDect;
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if(results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if(results == _gameObjects.end()) // Like EOF
		return NULL;
	return results->second; // Second item of pair
}

// Size wrapper
int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while(itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++; // A map can be reversed as well
	}
}

void GameObjectManager::UpdateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = clock.restart().asSeconds(); // Returns delta

	while(itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}
}

void GameObjectManager::CheckAllCollisions() {
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	std::map<std::string, VisibleGameObject*>::const_iterator subItr = _gameObjects.begin();

	VisibleGameObject* obj1 = NULL;
	VisibleGameObject* obj2 = NULL;

	while(itr != _gameObjects.end())
	{
		obj1 = itr->second;

		while(subItr != _gameObjects.end())
		{
			if(subItr->second == obj1) // Compare pointers
			{
				//std::cout << "CheckAllCollisions: Same obj\n"; // DEBUG
				subItr++;
			}
			else
			{
				//std::cout << "CheckAllCollisions: Assign obj2\n"; // DEBUG
				obj2 = subItr->second;
				subItr++;
			}
		}

		//std::cout << "CheckAllCollisions: Reset subItr\n";
		subItr = _gameObjects.begin(); // Start again for next object

		// We must have at least one obj1 if we got here, but need check for obj2
		if(obj2 != NULL)
		{
			//std::cout << "CheckAllCollisions: Obj2 not NULL\n"; // DEBUG
			if(_collDect->DetectCollision(obj1, obj2)) // See if they collide
			{
				std::cout << "CheckAllCollisions: Collision!\n"; // DEBUG
				obj1->AddCollidingObject(obj2);
				obj2->AddCollidingObject(obj1);
			}
		}
		itr++;
	}
}
