#pragma once

#include <map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class TextureManager
{
public:
    explicit TextureManager(SDL_Renderer *renderer) : mRenderer(renderer) {}

    ~TextureManager()
    {
        Clear();
    }

    SDL_Texture *AddTexture(const std::string &path)
    {
        auto it = textures.find(path);
        if (it != textures.end())
        {
            return it->second;
        }
        SDL_Texture *tex = IMG_LoadTexture(mRenderer, path.c_str());
            
        textures.emplace(path, tex);
        return tex;
    }

    void Clear()
    {
        for (auto &[_, tex] : textures)
        {
            SDL_DestroyTexture(tex);
        }
        textures.clear();
    }

private:
    SDL_Renderer *mRenderer;
    std::map<std::string, SDL_Texture *> textures;
};
