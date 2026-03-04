#include "GameEngine.h"
#include "Constants.h"
#include "GameObject.h"
#include "CollisionSystem.h"
#include "InputManager.h"
#include "TextureManager.h"
#include <string>

namespace GameEngine
{
    GameEngine engine{};
    InputManager inputManager{};
    TextureManager textureManager{engine.GetRenderer()};
    AudioManager audioManager{};

    GameEngine::GameEngine()
    {
        Init();
    }
    GameEngine::~GameEngine()
    {
        textureManager.Clear();
        gameObjects.clear();
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    void GameEngine::Run()
    {
        running = true;
        Uint64 frequency = SDL_GetPerformanceFrequency();
        lastCounter = SDL_GetPerformanceCounter();
        while (running)
        {
            Uint64 currentCounter = SDL_GetPerformanceCounter();
            deltaTime = static_cast<double>(currentCounter - lastCounter) / frequency;
            deltaTime = std::min(deltaTime, 0.1);
            lastCounter = currentCounter;

            Tick();

            if (fpsLimit > 0)
            {
                const double targetFrameTime = 1.0 / fpsLimit;
                if (deltaTime < targetFrameTime)
                {
                    SDL_Delay(static_cast<Uint32>((targetFrameTime - deltaTime) * 1000.0));
                }
            }
        }
    }

    void GameEngine::Tick()
    {
        Input();
        Update();
        Draw();
    }

    void GameEngine::Input()
    {
        inputManager.BeginFrame();
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            // for (auto &obj : gameObjects)
            //     obj->OnEvent(event);

            inputManager.HandleEvent(event);
        }
        inputManager.Update();
    }

    void GameEngine::Update()
    {
        physicsSystem.Update();
        collisionSystem.Update();
        for (size_t i = 0; i < gameObjects.size(); i++)
        {
            if (gameObjects[i])
                gameObjects[i]->Update();
        }

        for (int i = static_cast<int>(gameObjects.size()) - 1; i >= 0; --i)
        {
            if (gameObjects[i]->ShouldBeDestroyed())
            {
                gameObjects.erase(gameObjects.begin() + i);
            }
        }
    }

    void GameEngine::Draw()
    {
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);

        for (const auto &go : gameObjects)
        {
            if (go)
                go->Draw(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    void GameEngine::Init()
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Init(SDL_INIT_AUDIO);
        TTF_Init();
        window = SDL_CreateWindow("Game", constants::gScreenWidth, constants::gScreenHeight, 0);
        renderer = SDL_CreateRenderer(window, NULL);
    }

    void GameEngine::AddGameObject(std::unique_ptr<GameObject> gameObject)
    {
        gameObjects.push_back(std::move(gameObject));
    }

    void GameEngine::RemoveGameObject(GameObject *gameObject)
    {
        if (!gameObject)
            return;

        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
        {
            if (it->get() == gameObject)
            {
                gameObjects.erase(it);
                return;
            }
        }
    }

    void GameEngine::RemoveAllGameObjects()
    {
        gameObjects.clear();
    }
}