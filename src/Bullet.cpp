#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f& pos, sf::Vector2f& vel, sf::Texture& text)
    : m_pos(pos), m_vel(vel)
{
    m_sprite.setTexture(text);
    sf::Vector2f size = sf::Vector2f(text.getSize().x, text.getSize().y) * .5f;
    m_sprite.setOrigin(size);
    m_sprite.setPosition(m_pos);
    m_hitBox = sf::FloatRect(m_pos - size, size * 2.0f);
    m_halfSize = size;
}

sf::FloatRect Bullet::getHitbox()
{
    return m_hitBox;
}


sf::Vector2f Bullet::getPos()
{
    return m_pos;
}
    
void Bullet::update(sf::Time elapTime)
{
    m_pos += m_vel;
    m_sprite.setPosition(m_pos);
    m_hitBox = sf::FloatRect(m_pos - m_halfSize, m_halfSize * 2.0f);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}