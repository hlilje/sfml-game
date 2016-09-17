#include "stdafx.hpp"
#include "intent.hpp"


Intent::Intent(const IntentType type, const std::string & message) {
    _message = message;
}

void Intent::SetType(const IntentType intent) {
    _intent = intent;
}

Intent::IntentType Intent::GetType() {
    return _intent;
}

std::string Intent::GetIntentMessage() {
    return _message;
}
