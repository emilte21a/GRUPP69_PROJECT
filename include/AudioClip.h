#pragma once
#include "Component.h"
#include <GameEngine.h>

struct AudioClip
{
    SDL_AudioSpec spec;
    std::vector<Uint8> pcm;
};