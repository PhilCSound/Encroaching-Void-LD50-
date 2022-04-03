#include "LightMap.hpp"

LightMap::LightMap(unsigned int width, unsigned int height)
{
    m_renderText.create(width, height);
    m_sprite.setTexture(m_renderText.getTexture());
    m_renderText.clear(sf::Color(255, 255, 255, 0));
    m_image = m_renderText.getTexture().copyToImage();
}

void LightMap::AddLight(sf::Vector2f& pos, float radias)
{
    sf::CircleShape light(30);
    light.setRadius(radias);
    light.setPosition(pos - sf::Vector2f(radias, radias));
    light.setFillColor(sf::Color(255, 255, 255, 0));
    m_renderText.draw(light, sf::BlendNone);
    m_renderText.display();
}

void LightMap::AddVoid(sf::Vector2f& pos, float radias)
{
    sf::CircleShape dark(30);
    dark.setRadius(radias);
    dark.setPosition(pos - sf::Vector2f(radias, radias));
    dark.setFillColor(sf::Color(68,34,68,160));
    m_renderText.draw(dark, sf::BlendNone);
    m_renderText.display();
}


bool LightMap::checkCollision(sf::Vector2f pos, int radias)
{
    int x = pos.x;
    int y = pos.y;
    sf::Color col = m_image.getPixel(x, y); 
    return (col != sf::Color(255, 255, 255, 0));

}

void LightMap::update()
{
    frameCount += 1;
    if (frameCount < frameToUpdateImage)
        return;
    frameCount = 0;
    m_image = m_renderText.getTexture().copyToImage();
}

void LightMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

