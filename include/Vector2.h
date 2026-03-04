#pragma once
#include <SDL3/SDL.h>
#include <iostream>

struct Vector2
{
    Vector2()
    {
        x = 0;
        y = 0;
    }
    Vector2(float x, float y)
    {
        (*this).x = x;
        (*this).y = y;
    }

    float x;
    float y;

    Vector2 operator+(const Vector2 &rhs) const
    {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 operator-(const Vector2 &rhs) const
    {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    Vector2 &operator+=(const Vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2 &operator-=(const Vector2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2 &operator=(const Vector2 &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Vector2 operator*(const Vector2 &rhs) const
    {
        return Vector2(x * rhs.x, y * rhs.y);
    }

    Vector2 operator*(float rhs)
    {
        return Vector2(x * rhs, y * rhs);
    }

    bool operator==(const Vector2 &rhs)
    {
        return (x == rhs.x && y == rhs.y);
    }
    bool operator!=(const Vector2 &rhs)
    {
        return (x != rhs.x || y != rhs.y);
    }

    static float Distance(const Vector2 &lhs, const Vector2 &rhs)
    {
        return SDL_sqrt(SDL_pow(rhs.x - lhs.x, 2) + SDL_pow(rhs.y - lhs.y, 2));
    }

    Vector2 &Normalize()
    {
        float l = SDL_sqrt(SDL_pow(x, 2) + SDL_pow(y, 2));
        if (l != 0.0f)
        {
            x /= l;
            y /= l;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec);
};

inline std::ostream &operator<<(std::ostream &os, const Vector2 &vec)
{
    os << "X: " << vec.x << " Y: " << vec.y << std::endl;

    return os;
}