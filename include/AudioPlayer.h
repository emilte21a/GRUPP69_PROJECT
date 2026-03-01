#pragma once
#include "Component.h"
#include <GameEngine.h>

struct AudioClip;
class AudioPlayer : public Component
{   
    public:
        AudioPlayer();
        ~AudioPlayer();
        void Play();
        void SetAudioClip(AudioClip& clip) {
            this->clip = &clip;
        }
    private:
        AudioClip* clip;
        SDL_AudioDeviceID deviceID = 0;
        SDL_AudioStream* audioStream;
};