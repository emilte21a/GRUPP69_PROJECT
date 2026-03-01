#pragma once

#include <map>
#include <SDL3/SDL.h>
#include "AudioClip.h"
#include <SDL3/SDL_audio.h>

class AudioManager
{
public:
    AudioClip LoadWav(const std::string path)
    {

        AudioClip clip;
        Uint8 *buffer = nullptr;
        Uint32 length = 0;

        if (!SDL_LoadWAV(path.c_str(), &clip.spec, &buffer, &length))
        {
            return AudioClip();
        }

        clip.pcm.assign(buffer, buffer + length);
        SDL_free(buffer);

        return clip;
    }
};