#pragma once
#include "Entity.h"
class Player : public Entity
{
public:
    Player();
    void Start() override;
    void Update() override;
    void OnCollision(GameObject &other) override;
    void OnEvent(const SDL_Event &event) override;
    int GetLastDirectionX();

private:
    void HandleMove() override;
    void HandleJump() override;
    void HandleShooting();
    AudioClip jumpSFX;
};