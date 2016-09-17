#pragma once


class Intent {
public:
    enum IntentType {
        Null,
        GameOver,
        LoadLevel,
        Win
    };  

private:
    IntentType _intent;
    std::string _message;

public:
    Intent(const IntentType type, const std::string & message);

    void SetType(const IntentType intent);
    IntentType GetType();
    std::string GetIntentMessage();
};