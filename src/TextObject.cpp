#include "TextObject.h"
#include <GameEngine.h>

TextObject::TextObject(const std::string &text, const std::string &fontPath, int fontSize, Color color)
{
    value = text;
    textColor = SDL_Color(color.r, color.g, color.b, color.a);

    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    AddComponent<Renderer>();
    rendererComponent = GetComponent<Renderer>();
    SetTag("Text");
    RebuildTexture();
}

TextObject::~TextObject()
{
    if (texture)
        SDL_DestroyTexture(texture);

    if (font)
        TTF_CloseFont(font);
}

void TextObject::SetText(const std::string &newText)
{
    value = newText;
    RebuildTexture();
}

void TextObject::RebuildTexture()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, value.c_str(), value.length(), textColor);
    if (!surface)
        return;

    texture = SDL_CreateTextureFromSurface(GameEngine::engine.GetRenderer(), surface);

    rect.w = static_cast<float>(surface->w);
    rect.h = static_cast<float>(surface->h);

    SDL_DestroySurface(surface);

    rendererComponent->SetTexture(texture);
}