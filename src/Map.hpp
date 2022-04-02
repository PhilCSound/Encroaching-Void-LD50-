#pragma once
#include "SFML/Graphics.hpp"

class Map : public sf::Drawable
{

public:
    Map();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
private:
    const sf::Vector2f TILE_SIZE { 16.0f, 16.0f};
    const sf::Vector2f MAP_BOUNDS { 800.0f, 600.0f};
    sf::Texture m_floorTexture;
    sf::Texture m_wallTexture;
    sf::Sprite m_wallSprites;
    sf::Sprite m_floorSprites;
};

