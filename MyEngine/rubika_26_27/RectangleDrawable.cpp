#include "RectangleDrawable.h"


RectangleDrawable::RectangleDrawable(sf::Vector2f size): IDrawable(), Shape(size)
{
    Drawable = &Shape;
}

void RectangleDrawable::Start()
{
}

void RectangleDrawable::Update(float deltaTime)
{
}

void RectangleDrawable::Destroy(float deltaTime)
{
}
