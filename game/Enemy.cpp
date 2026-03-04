#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "PhysicsBody.h"
#include <GameEngine.h>
#include <iostream>

Enemy::Enemy() : Entity()
{
    position = Vector2(300, 0);
    gravityStrength = 400;
    moveSpeed = 50;
    jumpForce = 150;

    GetComponent<PhysicsBody>()->SetShouldUseGravity(true);
    GetComponent<PhysicsBody>()->SetGravityStrength(gravityStrength);
    GetComponent<Renderer>()->SetTexture(GameEngine::textureManager.AddTexture(constants::fiende_str));
    SetTag("Enemy");
}

void Enemy::Update()
{
    GameObject::Update();
    HandleMove();
    HandleJump();
    GetComponent<Renderer>()->SetDirectionMultiplier(dir);
}

void Enemy::OnCollision(GameObject &other)
{
    if (other.GetTag() == "Bullet")
    {
        MarkForDestruction();
        other.MarkForDestruction();
    }
}

void Enemy::OnEvent(const SDL_Event &event)
{
}

float timer = 0;
void Enemy::HandleMove()
{
    timer += GameEngine::engine.GetDeltaTime();
    if (timer >= 1.0)
    {
        dir *= -1;
        timer -= 1.0;
    }

    auto *pB = GetComponent<PhysicsBody>();

    pB->SetVelocity(Vector2(dir * moveSpeed, pB->GetVelocity().y));
}

void Enemy::HandleJump()
{
    const auto &pB = GetComponent<PhysicsBody>();
    if (pB->IsGrounded())
    {
        srand(time(0));
        if (rand() % 101 >= 50)
        {
            pB->SetVelocity(Vector2(pB->GetVelocity().x, -jumpForce));
        }
    }
}
