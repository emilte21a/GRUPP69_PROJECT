#include "Game.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"
#include "TextObject.h"
#include <GameEngine.h>

Game::Game()
{
    GameEngine::engine.SetFpsLimit(160);
    GameEngine::engine.SetBackgroundColor(255, 255, 255, 255);
    GameEngine::engine.AddGameObject(std::make_unique<Player>());
    GameEngine::engine.AddGameObject(std::make_unique<Enemy>());
    PlaceTiles();
    PlacePlatforms();
    auto text = std::make_unique<TextObject>(
        "Hello world",
        constants::arial_str, 32, Color{0, 0, 0, 255});

    text->SetPosition({200, 200});
    GameEngine::engine.AddGameObject(std::move(text));
}

Game::~Game()
{
    GameEngine::engine.RemoveAllGameObjects();
}

void Game::PlacePlatforms()
{
    for (int i = 0; i < 3; ++i)
    {
        auto t = std::make_unique<Tile>();
        t->SetPosition(Vector2(100 + i * (constants::unitSize), constants::gScreenHeight - 200));

        GameEngine::engine.AddGameObject(std::move(t));
    }
}

void Game::PlaceTiles()
{
    for (size_t x = 0; x < 20; x++)
    {
        for (size_t y = 0; y < 2; y++)
        {
            auto t = std::make_unique<Tile>();
            t->SetPosition(Vector2(100 + x * constants::unitSize, constants::gScreenHeight - 100 + y * constants::unitSize));
            GameEngine::engine.AddGameObject(std::move(t));
        }
    }
}