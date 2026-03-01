#pragma once
#include "GameObject.h"
namespace GameEngine
{
    class PhysicsSystem
    {
    public:
        PhysicsSystem() = default;
        ~PhysicsSystem() = default;
        PhysicsSystem(const PhysicsSystem &) = delete;
        PhysicsSystem &operator=(const PhysicsSystem &) = delete;

        void Update();

    private:
        float terminalVelocity = 70;
    };
}