#include "stdafx.h"
#include "Intent.h"

Intent::Intent(std::string message)
{
	_message = message;
}

Intent::~Intent() { }

void Intent::SetType(IntentType intent)
{
	_intent = intent;
}

Intent::IntentType Intent::GetType()
{
	return _intent;
}

std::string Intent::GetIntentMessage()
{
	return _message;
}
