#pragma once
#include "IComponent.h"
#include "IDrawable.h"


class Entity;


class RenderComponent : public IDrawable, public IComponent
{
public:
    RenderComponent(Entity& parent);
    ~RenderComponent() override;
    
    
    void SetTransform(sf::Transform& transform);
    void SetDrawable(sf::Drawable* drawable);
    
    bool IsVisible() const { return Visible; }
    
    
};
