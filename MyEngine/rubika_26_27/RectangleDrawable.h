#pragma once
#include "IDrawable.h"
#include <SFML/Graphics/RectangleShape.hpp>

class RectangleDrawable : IDrawable
{
public:
	explicit RectangleDrawable(sf::Vector2f size = sf::Vector2f(0.f, 0.f));
    ~RectangleDrawable() override = default;
    
    void Start() override;
    void Update(float deltaTime) override;
    void Destroy(float deltaTime) override;
    
private:
    
    sf::RectangleShape Shape;
    
};
