#include "Enemy.h"
#include "Renderer.h"
#include "PhysicsBody.h"
#include <GameEngine.h>
#include <iostream>

Enemy::Enemy()
{
    Entity();
    position = Vector2(200, 0);
    gravityStrength = 400;
    moveSpeed = 50;
    jumpForce = 150;
   
    GetComponent<PhysicsBody>()->SetShouldUseGravity(true);
    GetComponent<PhysicsBody>()->SetGravityStrength(gravityStrength);
    GetComponent<Renderer>()->SetTexture(GameEngine::textureManager.AddTexture(constants::fiende_str));
}

void Enemy::Update()
{
    GameObject::Update();
    HandleMove();
    HandleJump();
    GetComponent<Renderer>()->SetDirectionMultiplier(dir);
}

void Enemy::OnCollision()
{
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

    position.x += dir * moveSpeed * GameEngine::engine.GetDeltaTime();
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
