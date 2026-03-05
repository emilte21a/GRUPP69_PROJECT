#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "PhysicsBody.h"
#include "Collider.h"
class Entity : public GameObject
{
public:
    Entity()
    {
        AddComponent<Collider>();
        AddComponent<PhysicsBody>();
        AddComponent<Renderer>();
    }
    int GetMoveSpeed() { return moveSpeed; }

protected:
    virtual void HandleMove() {}
    virtual void HandleJump() {}
    // konstig design-val av mig att lägga in alla dessa variabler försig, men det får vara så nu :D
    int moveSpeed = 100;
    int jumpForce = 200;
    int gravityStrength = 400;
    bool canJump = true;
    int dir = 1;
};