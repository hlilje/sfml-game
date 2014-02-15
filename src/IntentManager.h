// Manages and stores the current intents of the game.

#pragma once
#include "Intent.h"

class IntentManager
{
public:
	IntentManager();
	~IntentManager();

	void Add(Intent);
	Intent GetNext();
	void Clear();

private:
	std::deque<Intent> _intents;
};
