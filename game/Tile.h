#pragma once

#include "GameObject.h"
class Tile : public GameObject
{
public:
    Tile();
    void Update() override { GameObject::Update(); }
    void OnCollision(GameObject &other) override {}
};