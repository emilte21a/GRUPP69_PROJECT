#pragma once
#include "Component.h"
#include "Vector2.h"
#include <GameEngine.h>
#include <math.h>
class PhysicsBody : public Component
{
    class GameObject;

public:
    PhysicsBody() : Component() {}
    bool &ShouldUseGravity() { return useGravity; }
    void SetShouldUseGravity(bool g) { useGravity = g; }
    // Set new gravity strength. Default is 200
    void SetGravityStrength(float newGravityStrength) { gravity = newGravityStrength; }
    float GetGravityStrength() { return gravity; }
    Vector2 &GetVelocity() { return velocity; }
    void SetVelocity(const Vector2 &newVelocity) { velocity = newVelocity; }
    bool IsGrounded() const { return grounded; } // std::fabs(velocity.y) < 0.05f; }
    void SetGrounded(bool setGrounded) { grounded = setGrounded; }
    bool IsTrigger() const { return isTrigger; }
    void SetIsTrigger(bool shouldBeTrigger) { isTrigger = shouldBeTrigger; }

private:
    float gravity = 200.0;
    Vector2 velocity = {0, 0};
    float elasticity = 1;
    bool useGravity = false;
    bool grounded = false;
    bool isTrigger = false;
};