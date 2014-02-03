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

void GameObjectManager::RemoveAll()
{
	std::map<std::string, VisibleGameObject*>::iterator it = _gameObjects.begin();
	while(it != _gameObjects.end())
	{
		delete it->second;
		_gameObjects.erase(it);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if(results == _gameObjects.end())
		return NULL;
	return results->second;
}

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
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	float timeDelta = _clock.restart().asSeconds(); // Returns delta

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
			if(subItr->second == obj1)
			{
				subItr++;
				continue; // Continue since we didn't get obj2
			}
			else
			{
				obj2 = subItr->second;
				subItr++;
			}

			if(_collDect->DetectCollision(obj1, obj2))
			{
				obj1->AddCollidingObject(obj2);
				obj2->AddCollidingObject(obj1);
			}
		}

		subItr = _gameObjects.begin(); // Start again for next object

		itr++;
	}
}
