#include "RenderComponent.h"

RenderComponent::RenderComponent(Entity& parent) : 
    IComponent(parent),
    IDrawable()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Start()
{
}

void RenderComponent::Update(float fDeltaTime)
{
}

void RenderComponent::Destroy()
{
}

void RenderComponent::Destroy(float deltaTime)
{
}
