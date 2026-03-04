#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy();
    void Update() override;
    void OnCollision(GameObject &other) override;
    void OnEvent(const SDL_Event &event) override;

private:
    void HandleMove() override;
    void HandleJump() override;
};