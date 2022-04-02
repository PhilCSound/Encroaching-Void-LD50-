#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Map : public sf::Drawable
{

public:
    Map();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void checkBounds(sf::Vector2f& vel, sf::FloatRect& bounds);
private:
    const sf::Vector2f TILE_SIZE { 16.0f, 16.0f};
    const sf::Vector2f MAP_BOUNDS { 800.0f, 592.0f};
    sf::FloatRect m_collisionBox;
    sf::Texture m_floorTexture;
    sf::Texture m_wallTexture;
    sf::Sprite m_wallSprites;
    sf::Sprite m_floorSprites;
};

