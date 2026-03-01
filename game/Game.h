#pragma once

class Game
{
public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    const Game &operator=(const Game &) = delete;
    void PlacePlatforms();
    void PlaceTiles();
};