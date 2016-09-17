#pragma once


class Level {
public:
    enum LevelID {
        Level1
    };  

    bool Load(const Level::LevelID level);
};
