#pragma once
#include "Vector2.h"

class GameObject;
class Component
{

public:
    Component(const Component &) = delete;
    Component &operator=(const Component &) = delete;
    virtual ~Component() = default;
    virtual void Start() {}
    virtual void Update() {}
    void SetOwner(GameObject *owner) { this->owner = owner; }
    GameObject &GetOwner() const
    {
        if (!owner)
            throw std::runtime_error("Owner is null");
        return *owner;
    }

protected:
    Component() = default;
    GameObject *owner = nullptr;
};