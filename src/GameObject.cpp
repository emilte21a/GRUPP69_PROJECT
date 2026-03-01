#include "Component.h"
#include "GameObject.h"
#include "Constants.h"
#include "Renderer.h"

void GameObject::Update()
{
    rect.x = position.x;
    rect.y = position.y;
    for (auto &c : components)
        c->Update();
    
}

void GameObject::Draw(SDL_Renderer *ren)
{
    if (const auto &r = GetComponent<Renderer>())
    {
        r->Draw(ren);
    }
}