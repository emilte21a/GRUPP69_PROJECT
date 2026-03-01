#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "AudioManager.h"

namespace GameEngine
{
    class GameEngine
    {
    public:
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine &) = delete;
        GameEngine &operator=(const GameEngine &) = delete;
        void Run();
        SDL_Renderer *GetRenderer() const
        {
            return renderer;
        }
        void AddGameObject(std::unique_ptr<GameObject> gameObject);
        void RemoveGameObject(GameObject* gameObject);
        void RemoveAllGameObjects();
        std::vector<std::unique_ptr<GameObject>> &getGameObjects() { return gameObjects; }
        float GetDeltaTime() { return deltaTime; }
        void SetFpsLimit(int newLimit) { fpsLimit = fpsLimit > 0 ? newLimit : 0; }
        void SetBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { bgColor = {r, g, b, a}; }

    private:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        CollisionSystem collisionSystem {};
        PhysicsSystem physicsSystem {};

        void Update();
        void Draw();
        void Input();
        void Init();
        void Tick();
        int fpsLimit = 60;
        bool running = true;
        Uint64 lastCounter = 0;
        double deltaTime = 0.0;
        SDL_Color bgColor = {0, 0, 0, 255};
    };

    extern GameEngine engine;
    extern InputManager inputManager;
    extern TextureManager textureManager;
    extern AudioManager audioManager;
}