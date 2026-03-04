#include "Player.h"
#include "Bullet.h"
#include "Renderer.h"
#include "PhysicsBody.h"
#include "AudioPlayer.h"
#include <GameEngine.h>
#include <iostream>

Player::Player() : Entity()
{
    position = Vector2(100, 0);
    GetComponent<PhysicsBody>()->SetShouldUseGravity(true);
    GetComponent<PhysicsBody>()->SetGravityStrength(gravityStrength);
    GetComponent<Renderer>()->SetTexture(GameEngine::textureManager.AddTexture(constants::idle_str));
    AddComponent<AudioPlayer>();
    jumpSFX = GameEngine::audioManager.LoadWav(constants::jump_str);
    GetComponent<AudioPlayer>()->SetAudioClip(jumpSFX);
    SetTag("Player");
}

void Player::Update()
{
    GameObject::Update();
    HandleMove();
    HandleJump();
    HandleShooting();
    GetComponent<Renderer>()->SetDirectionMultiplier(GetLastDirectionX());
}

void Player::HandleMove()
{
    float axis = GameEngine::inputManager.GetAxisX();

    float moveX = axis * moveSpeed;
    auto *pB = GetComponent<PhysicsBody>();
    Vector2 velo (moveX, pB->GetVelocity().y);
    pB->SetVelocity(velo);  
}

void Player::HandleShooting()
{
    if (GameEngine::inputManager.IsMouseButtonPressed(GameEngine::InputManager::MouseButton::Left))
    {

        auto bullet = std::make_unique<Bullet>();
        bullet->SetPosition(position);

        Vector2 mousePos{GameEngine::inputManager.GetMousePosition()};
        Vector2 direction = mousePos - position;

        direction.Normalize();

        bullet->GetComponent<PhysicsBody>()->SetVelocity(direction * bullet->GetMoveSpeed());

        GameEngine::engine.AddGameObject(std::move(bullet));
    }
}

void Player::HandleJump()
{
    const auto &pB = GetComponent<PhysicsBody>();

    if (GameEngine::inputManager.IsKeyDown(GameEngine::InputManager::Key::Space))
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

void Player::OnCollision(GameObject &other)
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