#include "PhysicsSystem.h"
#include <GameEngine.h>
#include "PhysicsBody.h"
namespace GameEngine
{
    void PhysicsSystem::Update()
    {
        for (auto &go : engine.getGameObjects())
        {
            auto *pB = go->GetComponent<PhysicsBody>();

            if (!pB)
                continue;

            pB->SetGrounded(false);

            if (pB->ShouldUseGravity())
            {
                pB->GetVelocity().y += pB->GetGravityStrength() * engine.GetDeltaTime();
            }

            pB->owner->GetPosition() += ((pB->GetVelocity() * engine.GetDeltaTime()));
        }
    }
}