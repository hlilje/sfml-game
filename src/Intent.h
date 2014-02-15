// An intent object to communicate changes of game state while
// inside a playing state.

#pragma once

class Intent
{
public:
	Intent(std::string);
	~Intent();

	enum IntentType { Win, GameOver, LoadLevel };  

	void SetType(IntentType);
	IntentType GetType();
	std::string GetIntentMessage();

private:
	IntentType _intent;
	std::string _message;
};