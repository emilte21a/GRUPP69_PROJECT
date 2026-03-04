#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <type_traits>
#include "Vector2.h"
#include "Constants.h"
#include "Component.h"
#include <ostream>

class GameObject
{

public:
    // bort med copy constrcutorororaor
    GameObject(const GameObject &) = delete;
    const GameObject &operator=(const GameObject &) = delete;

    virtual ~GameObject() = default;
    virtual void Update();
    virtual void Draw(SDL_Renderer *ren);
    const SDL_FRect &GetRect() const { return rect; }

    virtual void OnEvent(const SDL_Event &) {}
    virtual void OnCollision(GameObject &other) {}

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    T *GetComponent()
    {
        for (const auto &c : components)
        {
            if (auto ptr = dynamic_cast<T *>(c.get()))
                return ptr;
        }
        return nullptr;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
    void AddComponent()
    {
        auto comp = std::make_unique<T>();
        comp->owner = this;
        components.push_back(std::move(comp));
    }

    Vector2 &GetPosition() { return position; }
    void SetPosition(const Vector2 &newPos) { position = newPos; }
    void SetTag(std::string newTag) { tag = newTag; }
    void MarkForDestruction() { shouldBeDestroyed = true; }
    bool ShouldBeDestroyed() { return shouldBeDestroyed; }
    std::string GetTag() { return tag; }

protected:
    GameObject() = default;
    SDL_FRect rect = {0, 0, constants::unitSize, constants::unitSize};
    std::vector<std::unique_ptr<Component>> components;
    Vector2 position = {0, 0};
    std::string tag = "GameObject";
    bool shouldBeDestroyed = false;

private:
    friend std::ostream &operator<<(std::ostream &os, GameObject &obj);
};

inline std::ostream &operator<<(std::ostream &os, GameObject &obj)
{
    os << typeid(obj).name();
    return os;
}