#include <GameEngine.h>
#include <SDL3/SDL.h>
#include "../game/Game.h"

int main()
{
  Game game{};
  GameEngine::engine.Run();

  return 0;
}