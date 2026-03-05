#include "Tile.h"
#include <GameEngine.h>
#include "GameObject.h"
#include "Renderer.h"
#include "Collider.h"

Tile::Tile(){
    AddComponent<Collider>();
    AddComponent<Renderer>();
    
}