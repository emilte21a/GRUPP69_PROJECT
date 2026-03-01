#include "Player.h"
#include "Renderer.h"
#include "PhysicsBody.h"
#include "AudioPlayer.h"
#include <GameEngine.h>
#include <iostream>

Player::Player()
{
    Entity();
    position = Vector2(100, 0);
    GetComponent<PhysicsBody>()->SetShouldUseGravity(true);
    GetComponent<PhysicsBody>()->SetGravityStrength(gravityStrength);
    GetComponent<Renderer>()->SetTexture(GameEngine::textureManager.AddTexture(constants::idle_str));
    AddComponent<AudioPlayer>();
    jumpSFX = GameEngine::audioManager.LoadWav(constants::sample_str);
    GetComponent<AudioPlayer>()->SetAudioClip(jumpSFX);
}

void Player::Update()
{
    GameObject::Update();
    HandleMove();
    HandleJump();

    GetComponent<Renderer>()->SetDirectionMultiplier(GetLastDirectionX());
}

void Player::HandleMove()
{
    float moveX = GameEngine::inputManager.GetAxisX() * moveSpeed * GameEngine::engine.GetDeltaTime();
    position.x += moveX;
}

void Player::HandleJump()
{
    const auto &pB = GetComponent<PhysicsBody>();

    if (GameEngine::inputManager.IsKeyDown(InputManager::Key::Space))
    {
        if (pB->IsGrounded())
        {
            pB->SetVelocity(Vector2(pB->GetVelocity().x, -jumpForce));
            GetComponent<AudioPlayer>()->Play();
        }
    }

    if (pB->GetVelocity().y > 0)
        pB->SetGravityStrength(gravityStrength * 2);
    else
        pB->SetGravityStrength(gravityStrength);
}

void Player::OnEvent(const SDL_Event &event)
{
}

void Player::OnCollision()
{
}

int Player::GetLastDirectionX()
{
    if (GameEngine::inputManager.GetAxisX() > 0)
        dir = 1;
    else if (GameEngine::inputManager.GetAxisX() < 0)
        dir = -1;

    return dir;
}