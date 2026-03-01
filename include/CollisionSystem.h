#pragma once
#include "GameObject.h"
namespace GameEngine
{
    class CollisionSystem
    {
    public:
        CollisionSystem() = default;
        ~CollisionSystem() = default;
        CollisionSystem(const CollisionSystem &) = delete;
        CollisionSystem &operator=(const CollisionSystem &) = delete;
        void Update();
        static bool CheckCollision(const SDL_FRect &a, const SDL_FRect &b);

    private:
        static SDL_FRect GetCollisionRectangle(const SDL_FRect &a, const SDL_FRect &b);

        enum axis
        {
            x,
            y
        };

        static void HandleCollision(GameObject *a, GameObject *b, axis axis);
    };
}