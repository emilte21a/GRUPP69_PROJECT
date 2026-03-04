#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() : clip(nullptr), deviceID(0), audioStream(nullptr)
{
}

AudioPlayer::~AudioPlayer()
{
    if (audioStream)
    {
        SDL_DestroyAudioStream(audioStream);
    }
    if (deviceID != 0)
    {
        SDL_CloseAudioDevice(deviceID);
        deviceID = 0;
    }
}

void AudioPlayer::Play()
{
    if (!clip || clip->pcm.empty())
        return;
    
    if (deviceID == 0)
    {
        deviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (deviceID == 0)
            return;

        SDL_AudioSpec deviceSpec{};
        SDL_GetAudioDeviceFormat(deviceID, &deviceSpec, nullptr);

        audioStream = SDL_CreateAudioStream(
            &clip->spec, 
            &deviceSpec  
        );

        if (!audioStream)
            return;

        SDL_BindAudioStream(deviceID, audioStream);
    }

    SDL_PutAudioStreamData(
        audioStream,
        clip->pcm.data(),
        static_cast<int>(clip->pcm.size()));

    SDL_ResumeAudioDevice(deviceID);
}
