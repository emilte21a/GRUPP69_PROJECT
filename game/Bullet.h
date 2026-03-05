#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
    Bullet() : Entity()
    {
        rect.w /= 8;
        rect.h /= 8;
        moveSpeed = 400;
        GetComponent<PhysicsBody>()->SetShouldUseGravity(false);
        GetComponent<Collider>()->SetIsTrigger(true);
        SetTag("Bullet");
    }

    void Update() override
    {
        GameObject::Update();
        age += GameEngine::engine.GetDeltaTime();

        if (age >= lifeTime)
        {
            MarkForDestruction();
        }
    }

    void OnCollision(GameObject &other) override
    {
    }
    void OnEvent(const SDL_Event &event) override
    {
    }

private:
    float lifeTime = 10;
    float age = 0;
};