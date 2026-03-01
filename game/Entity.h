#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "PhysicsBody.h"
class Entity : public GameObject
{
public:
    Entity()
    {
        AddComponent<PhysicsBody>();
        AddComponent<Renderer>();
    }

protected:
    virtual void HandleMove() {}
    virtual void HandleJump() {}
    int moveSpeed = 100;
    int jumpForce = 200;
    int gravityStrength = 400;
    bool canJump = true;
    int dir = 1;
};