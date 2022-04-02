#include "Map.hpp"

Map::Map()
{
    m_floorTexture.loadFromFile("resources/gfx/WoodTile.png");
    m_wallTexture.loadFromFile("resources/gfx/WoodWall.png");
    m_floorTexture.setRepeated(true);
    m_wallTexture.setRepeated(true);
    m_floorTexture.setSmooth(true);
    m_wallTexture.setSmooth(true);
    m_wallSprites.setTexture(m_wallTexture);
    m_wallSprites.setTextureRect(sf::IntRect(0,0,832,632));
    m_wallSprites.setOrigin(16,16);
    m_floorSprites.setTexture(m_floorTexture);
    m_floorSprites.setTextureRect(sf::IntRect(0,0,800,600));

    
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_wallSprites, states);
    target.draw(m_floorSprites, states);
}