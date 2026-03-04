#pragma once
#include "GameObject.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Renderer.h"

struct Color
{
    Color(int8_t r, int8_t g, int8_t b, int8_t a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    Color(int r, int g, int b, int a)
    {
        this->r = static_cast<int>(r);
        this->g = static_cast<int>(g);
        this->b = static_cast<int>(b);
        this->a = static_cast<int>(a);

    }

    int8_t r, g, b, a = 255;
};

class TextObject : public GameObject
{
public:
    TextObject(const std::string &text, const std::string &fontPath, int fontSize, Color color);
    ~TextObject();

    void SetText(const std::string &newText);

private:
    void RebuildTexture();
    SDL_Texture *texture = nullptr;
    TTF_Font *font = nullptr;

    std::string value;
    SDL_Color textColor;

    Renderer* rendererComponent = nullptr;
};