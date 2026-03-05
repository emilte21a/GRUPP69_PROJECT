#include "EnemySpawner.h"
#include <GameEngine.h>
#include "Enemy.h"

void EnemySpawner::Start()
{
}
float enemySpawnTimer = 0;
float enemySpawnInterval = 10;
void EnemySpawner::Update()
{
    if (enemySpawnTimer <= 0)
    {
        enemySpawnTimer = enemySpawnInterval;
        GameEngine::engine.AddGameObject(std::make_unique<Enemy>());
    }
    enemySpawnTimer -= GameEngine::engine.GetDeltaTime();
}