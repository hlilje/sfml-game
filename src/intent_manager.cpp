#include "stdafx.hpp"
#include "intent_manager.hpp"


IntentManager::~IntentManager() {
    Clear();
}

void IntentManager::Add(const Intent intent) {
    _intents.push_back(intent);
}

Intent IntentManager::GetNext() {
    if (_intents.empty())
        return Intent(Intent::IntentType::Null, "");

    Intent intent = _intents.front();
    _intents.pop_front();

    return intent;
}

void IntentManager::Clear() {
    _intents.clear();
}