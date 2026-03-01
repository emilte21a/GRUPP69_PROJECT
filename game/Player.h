#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
    Player();
    void Update() override;
    void OnCollision() override;
    void OnEvent(const SDL_Event &event) override;
    int GetLastDirectionX();

private:
    void HandleMove() override;
    void HandleJump() override;
    AudioClip jumpSFX;
};