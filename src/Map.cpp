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
    //Collison box, kinda hacky, but hey might just work...
    m_collisionBox = sf::FloatRect(TILE_SIZE, MAP_BOUNDS - TILE_SIZE * 2.0f);
    
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_wallSprites, states);
    target.draw(m_floorSprites, states);
}

bool Map::checkBounds(sf::Vector2f& vel, sf::FloatRect& bounds)
{
    sf::Vector2f size = sf::Vector2f(bounds.width, bounds.height);
    sf::Vector2f calcPos = vel + sf::Vector2f(bounds.left, bounds.top);
    sf::FloatRect tempBounds = sf::FloatRect(calcPos, size);

    if (m_collisionBox.intersects(tempBounds))
        return false;
    if (calcPos.x <= 0)
        vel.x = 0 - bounds.left;
    if (calcPos.x >= MAP_BOUNDS.x)
        vel.x -= calcPos.x - MAP_BOUNDS.x;
    if (calcPos.y <= 0)
        vel.y = 0 - bounds.top;
    if (calcPos.y >= MAP_BOUNDS.y)
        vel.y -= calcPos.y - MAP_BOUNDS.y;
    return true;
}