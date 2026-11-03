#pragma once
#include "IDrawable.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class SpriteDrawable : IDrawable
{
public:
    
    explicit SpriteDrawable(const sf::Texture& texture);
    ~SpriteDrawable() override;
    
    void Start() override;
    void Update(float deltaTime) override;
    void Destroy(float deltaTime) override;
    
private:
    sf::Sprite Sprite;
    
};
