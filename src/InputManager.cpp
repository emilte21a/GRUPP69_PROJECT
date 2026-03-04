#include "InputManager.h"
#include <SDL3/SDL.h>
#include <GameEngine.h>
namespace GameEngine
{

    static InputManager::Key SDLToEngineKey(SDL_Scancode sc)
    {
        using Key = InputManager::Key;

        switch (sc)
        {
        case SDL_SCANCODE_A:
            return Key::A;
        case SDL_SCANCODE_D:
            return Key::D;
        case SDL_SCANCODE_W:
            return Key::W;
        case SDL_SCANCODE_S:
            return Key::S;

        case SDL_SCANCODE_ESCAPE:
            return Key::Escape;
        case SDL_SCANCODE_SPACE:
            return Key::Space;
        case SDL_SCANCODE_RETURN:
            return Key::Enter;
        case SDL_SCANCODE_TAB:
            return Key::Tab;
        case SDL_SCANCODE_BACKSPACE:
            return Key::Backspace;

        case SDL_SCANCODE_LEFT:
            return Key::Left;
        case SDL_SCANCODE_RIGHT:
            return Key::Right;
        case SDL_SCANCODE_UP:
            return Key::Up;
        case SDL_SCANCODE_DOWN:
            return Key::Down;

        default:
            return Key::Unknown;
        }
    }

    static InputManager::MouseButton SDLToEngineMouse(Uint8 button)
    {
        using MB = InputManager::MouseButton;

        switch (button)
        {
        case SDL_BUTTON_LEFT:
            return MB::Left;
        case SDL_BUTTON_RIGHT:
            return MB::Right;
        case SDL_BUTTON_MIDDLE:
            return MB::Middle;
        default:
            return MB::Left;
        }
    }

    void InputManager::BeginFrame()
    {
        prevKeys = currentKeys;
        prevMouse = currentMouse;
    }

    void InputManager::HandleEvent(const SDL_Event &event)
    {

        switch (event.type)
        {
        case SDL_EVENT_KEY_DOWN:
        {
            Key key = SDLToEngineKey(event.key.scancode);
            if (key != Key::Unknown)
                currentKeys[ToIndex(key)] = true;
            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            Key key = SDLToEngineKey(event.key.scancode);
            if (key != Key::Unknown)
                currentKeys[ToIndex(key)] = false;
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            MouseButton mb = SDLToEngineMouse(event.button.button);
            currentMouse[ToIndex(mb)] = true;
            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            MouseButton mb = SDLToEngineMouse(event.button.button);
            currentMouse[ToIndex(mb)] = false;
            break;
        }

        default:
            break;
        }
    }

    void InputManager::Update()
    {
        float x, y;
        SDL_GetMouseState(&x, &y);
        mousePosition = {x, y};
    }

    bool InputManager::IsKeyDown(Key key) const
    {
        return currentKeys[ToIndex(key)];
    }

    bool InputManager::IsKeyPressed(Key key) const
    {
        size_t i = ToIndex(key);
        return currentKeys[i] && !prevKeys[i];
    }

    bool InputManager::IsKeyReleased(Key key) const
    {
        size_t i = ToIndex(key);
        return !currentKeys[i] && prevKeys[i];
    }

    bool InputManager::IsMouseButtonDown(MouseButton button) const
    {
        return currentMouse[ToIndex(button)];
    }

    bool InputManager::IsMouseButtonPressed(MouseButton button) const
    {
        size_t i = ToIndex(button);
        return currentMouse[i] && !prevMouse[i];
    }

    bool InputManager::IsMouseButtonReleased(MouseButton button) const
    {
        size_t i = ToIndex(button);
        return !currentMouse[i] && prevMouse[i];
    }

    Vector2 InputManager::GetMousePosition() const
    {
        return mousePosition;
    }

    size_t InputManager::ToIndex(Key key)
    {
        return static_cast<size_t>(key);
    }

    size_t InputManager::ToIndex(MouseButton button)
    {
        return static_cast<size_t>(button);
    }
}