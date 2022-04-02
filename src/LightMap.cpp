#include "LightMap.hpp"

LightMap::LightMap(unsigned int width, unsigned int height)
{
    m_renderText.create(width, height);
    m_sprite.setTexture(m_renderText.getTexture());
    m_renderText.clear(sf::Color::White);
}

void LightMap::AddLight(sf::Vector2f& pos, float radias)
{
    sf::CircleShape light(30);
    light.setRadius(radias);
    light.setPosition(pos - sf::Vector2f(radias, radias));
    light.setFillColor(sf::Color::Yellow);
    m_renderText.draw(light, sf::BlendAdd);
    m_renderText.display();
}


void LightMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
