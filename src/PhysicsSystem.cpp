#include "PhysicsSystem.h"
#include <GameEngine.h>
#include "PhysicsBody.h"
namespace GameEngine
{
    void PhysicsSystem::Update()
    {
        for (auto &go : engine.GetGameObjects())
        {
            auto *pB = go->GetComponent<PhysicsBody>();

            if (!pB)
                continue;

            pB->SetGrounded(false);

            if (pB->ShouldUseGravity())
            {
                pB->GetVelocity().y += pB->GetGravityStrength() * engine.GetDeltaTime();
            }
            Vector2 newPos = pB->GetOwner().GetPosition() + pB->GetVelocity() * engine.GetDeltaTime();
            pB->GetOwner().SetPosition(newPos);
        }
    }
}