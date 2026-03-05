#pragma once
#include "GameObject.h"

class EnemySpawner : public GameObject
{
public:
    EnemySpawner() : GameObject()
    {
    }

    void Start() override;
    void Update() override;
};