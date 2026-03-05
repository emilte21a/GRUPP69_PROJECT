#pragma once

#include "GameObject.h"
class Tile : public GameObject
{
public:
    Tile();
    void Start() override{}
    void Update() override { GameObject::Update(); }
    void OnCollision(GameObject &other) override {}
};