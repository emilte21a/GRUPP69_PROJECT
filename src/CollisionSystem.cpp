#include "CollisionSystem.h"
#include <GameEngine.h>
#include "PhysicsBody.h"
#include "GameObject.h"
#include "Constants.h"
#include <algorithm>
namespace GameEngine
{

    void CollisionSystem::Update()
    {
        auto &gameObjects = engine.GetGameObjects();

        for (size_t i = 0; i < gameObjects.size(); ++i)
        {
            for (size_t j = i + 1; j < gameObjects.size(); ++j)
            {
                GameObject *a = gameObjects[i].get();
                GameObject *b = gameObjects[j].get();

                if (!CheckCollision(a->GetRect(), b->GetRect()))
                    continue;

                if (a->GetTag() == "Text" || b->GetTag() == "Text")
                    continue;

                SDL_FRect collisionRect = GetCollisionRectangle(a->GetRect(), b->GetRect());
                axis resolveAxis = (collisionRect.w < collisionRect.h) ? x : y;

                auto aHasPB = a->GetComponent<PhysicsBody>() != nullptr;
                auto bHasPB = b->GetComponent<PhysicsBody>() != nullptr;

                bool isTriggerCollision = ((aHasPB && a->GetComponent<PhysicsBody>()->IsTrigger()) ||
                                           (bHasPB && b->GetComponent<PhysicsBody>()->IsTrigger()));

                if (isTriggerCollision)
                {
                    a->OnCollision(*b);
                    b->OnCollision(*a);
                    continue;
                }

                if (aHasPB)
                {
                    HandleCollision(a, b, resolveAxis);
                }
                else if (bHasPB)
                {
                    HandleCollision(b, a, resolveAxis);
                }
            }
        }
    }

    // AABB kollisionssvar
    void CollisionSystem::HandleCollision(GameObject *a, GameObject *b, CollisionSystem::axis axis)
    {
        auto pB = a->GetComponent<PhysicsBody>();
        if (!pB)
            return;

        SDL_FRect collisionRectangle = GetCollisionRectangle(a->GetRect(), b->GetRect());

        if (axis == y)
        {
            Vector2 pos = a->GetPosition();
            if (a->GetPosition().y < b->GetPosition().y)
            {
                pos.y -= collisionRectangle.h;
                pB->SetGrounded(true);
            }
            else
                pos.y += collisionRectangle.h;

            a->SetPosition(pos);
            pB->SetVelocity(Vector2(pB->GetVelocity().x, 0));
        }

        if (axis == x)
        {
            Vector2 pos = a->GetPosition();
            if (a->GetPosition().x < b->GetPosition().x)
                pos.x -= collisionRectangle.w;
            else
                pos.x += collisionRectangle.w;

            a->SetPosition(pos);
            pB->SetVelocity(Vector2(0, pB->GetVelocity().y));
        }
        a->OnCollision(*b);
        b->OnCollision(*a);
    }

    bool CollisionSystem::CheckCollision(const SDL_FRect &a, const SDL_FRect &b)
    {
        return SDL_HasRectIntersectionFloat(&a, &b);
    }

    SDL_FRect CollisionSystem::GetCollisionRectangle(const SDL_FRect &a, const SDL_FRect &b)
    {

        float x = std::max(a.x, b.x);
        float y = std::max(a.y, b.y);
        float right = std::min(a.x + a.w, b.x + b.w);
        float bottom = std::min(a.y + a.h, b.y + b.h);
        float width = right - x;
        float height = bottom - y;
        if (width < 0.0f)
            width = 0.0f;
        if (height < 0.0f)
            height = 0.0f;
        return SDL_FRect{x, y, width, height};
    }
}