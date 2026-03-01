#pragma once

#include <SDL3/SDL.h>
#include <vector>

class InputManager {
public:
    enum class Key {
        A, D, W, S, Space
    };

    void BeginFrame() {
        prevKeyState = currentKeyState;
    }

    void HandleEvent(const SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN) {
            currentKeyState[event.key.scancode] = true;
        } 
        else if (event.type == SDL_EVENT_KEY_UP) {
            currentKeyState[event.key.scancode] = false;
        }
    }

    void Update()
    {
        const bool *state = SDL_GetKeyboardState(nullptr);
        if (!state) return;
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
            currentKeyState[i] = state[i] != 0;
    }

    bool IsKeyDown(Key key) const {
        return currentKeyState[ScancodeFor(key)];
    }

    bool IsKeyPressed(Key key) const {
        int sc = ScancodeFor(key);
        return currentKeyState[sc] && !prevKeyState[sc];
    }

    bool IsKeyReleased(Key key) const {
        int sc = ScancodeFor(key);
        return !currentKeyState[sc] && prevKeyState[sc];
    }

    int GetAxisX() const {
        if (IsKeyDown(Key::A) && !IsKeyDown(Key::D)) return -1;
        if (IsKeyDown(Key::D) && !IsKeyDown(Key::A)) return 1;
        return 0;
    }

    int GetAxisY() const {
        if (IsKeyDown(Key::W)) return -1;
        if (IsKeyDown(Key::S)) return 1;
        return 0;
    }

private:
    static int ScancodeFor(Key key) {
        switch (key) {
        case Key::A: return SDL_SCANCODE_A;
        case Key::D: return SDL_SCANCODE_D;
        case Key::W: return SDL_SCANCODE_W;
        case Key::S: return SDL_SCANCODE_S;
        case Key::Space: return SDL_SCANCODE_SPACE;
        default: return SDL_SCANCODE_UNKNOWN;
        }
    }

    std::vector<bool> currentKeyState = std::vector<bool>(SDL_SCANCODE_COUNT, false);
    std::vector<bool> prevKeyState = std::vector<bool>(SDL_SCANCODE_COUNT, false);
};