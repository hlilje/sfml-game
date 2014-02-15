#include "stdafx.h"
#include "IntentManager.h"

IntentManager::IntentManager() { }

IntentManager::~IntentManager()
{
	Clear();
}

void IntentManager::Add(Intent intent)
{
	_intents.push_back(intent);
}

Intent IntentManager::GetNext()
{
	if (_intents.empty())
		return NULL;

	Intent intent = _intents.front();
	_intents.pop_front();
	return intent;
}

void IntentManager::Clear()
{
	_intents.clear();
}