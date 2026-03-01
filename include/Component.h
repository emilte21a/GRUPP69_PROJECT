#pragma once
#include "Vector2.h"
class GameObject;

class Component
{

public:
    Component(const Component &) = delete;
    Component &operator=(const Component &) = delete;
    virtual ~Component() = default;
    virtual void Update() {}
    GameObject *owner = nullptr;

protected:
    Component() = default;
};