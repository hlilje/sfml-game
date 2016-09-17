#pragma once

#include "intent.hpp"


class IntentManager {
private:
    std::deque<Intent> _intents;

public:
    ~IntentManager();

    void Add(const Intent intent);
    Intent GetNext();
    void Clear();
};
