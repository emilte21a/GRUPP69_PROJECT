#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Component.h"
#include "GameObject.h"
#include "GameEngine.h"

class Renderer : public Component
{
public:
    void SetTexture(SDL_Texture *newTex)
    {
        tex = newTex;
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    }

    void Draw(SDL_Renderer *ren)
    {
        SDL_FRect dst = owner->GetRect();
        int maxFrames = 0;
        if (tex)
        {
            int frameWidth = static_cast<int>(dst.w);
            if (frameWidth > 0)
                maxFrames = tex->w / frameWidth;
        }

        if (maxFrames > 1)
        {
            float timePerFrame = 0.3f;

            timer += GameEngine::engine.GetDeltaTime();

            if (timer >= timePerFrame)
            {
                timer = 0;
                currentFrame++;
            }
            currentFrame %= maxFrames;
        }

        SDL_FRect src{static_cast<float>(currentFrame) * dst.w, 0, dst.w, dst.h};

        SDL_FlipMode flipMode = SDL_FLIP_NONE;

        if (directionMultiplier != 1)
        {
            flipMode = SDL_FLIP_HORIZONTAL;
        }

        if (tex)
        {
            SDL_RenderTextureRotated(ren, tex, &src, &dst, 0, NULL, flipMode);
        }
        else
        {
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
            SDL_RenderFillRect(ren, &dst);
        }
    }

    void SetDirectionMultiplier(int newDir)
    {
        directionMultiplier = newDir;
    }

private:
    SDL_Texture *tex{nullptr};
    int directionMultiplier = 1;
    float timer = 0;
    int currentFrame = 0;
};