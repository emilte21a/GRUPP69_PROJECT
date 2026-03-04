#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <GameEngine.h>
namespace GameEngine
{
    class InputManager
    {
    public:
        // lätt men dumt sätt att hantera knapptryckningar
        enum class Key
        {
            Unknown = 0,

            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,

            Escape,
            Space,
            Enter,
            Tab,
            Backspace,

            Left,
            Right,
            Up,
            Down,

            Count
        };

        enum class MouseButton
        {
            Left = 0,
            Right,
            Middle,
            Count
        };

        void BeginFrame();
        void HandleEvent(const SDL_Event &event);
        void Update();

        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        bool IsMouseButtonDown(MouseButton button) const;
        bool IsMouseButtonPressed(MouseButton button) const;
        bool IsMouseButtonReleased(MouseButton button) const;

        Vector2 GetMousePosition() const;

        int GetAxisX() const
        {
            if (IsKeyDown(Key::A) && !IsKeyDown(Key::D))
                return -1;
            if (IsKeyDown(Key::D) && !IsKeyDown(Key::A))
                return 1;
            return 0;
        }

        int GetAxisY() const
        {
            if (IsKeyDown(Key::W))
                return -1;
            if (IsKeyDown(Key::S))
                return 1;
            return 0;
        }

    private:
        using KeyArray = std::array<bool, static_cast<size_t>(Key::Count)>;
        using MouseArray = std::array<bool, static_cast<size_t>(MouseButton::Count)>;

        KeyArray currentKeys{};
        KeyArray prevKeys{};

        MouseArray currentMouse{};
        MouseArray prevMouse{};

        Vector2 mousePosition{};

        static size_t ToIndex(Key key);
        static size_t ToIndex(MouseButton button);
    };
}