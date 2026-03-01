#include "Tile.h"
#include <GameEngine.h>
#include "GameObject.h"
#include "Renderer.h"

Tile::Tile(){
    AddComponent<Renderer>();
}