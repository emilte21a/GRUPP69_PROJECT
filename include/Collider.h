#pragma once
#include "Component.h"
class Collider : public Component
{

public:
    Collider() : Component() {}

    bool IsTrigger() const { return isTrigger; }
    void SetIsTrigger(bool shouldBeTrigger) { isTrigger = shouldBeTrigger; }
    const SDL_FRect& GetColliderRectangle() const
    {
        return GetOwner().GetRect();
    }

private:
    bool isTrigger = false;
};