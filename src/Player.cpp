#include "Player.hpp"

Player::Player()
{
    m_playerText.loadFromFile("resources/gfx/newPlayer.png");
    m_playerSprite.setTexture(m_playerText);
    m_playerSprite.setOrigin(sf::Vector2f(m_playerText.getSize()) * 0.5f);
    m_playerSprite.setPosition(m_pos);
}

void Player::AddVelocity(sf::Vector2f& velocity)
{
    m_vel += velocity;
}

void Player::Move()
{
    m_pos += m_vel;
    m_playerSprite.setPosition(m_pos);
}

void Player::LookAt(sf::Vector2f& pos)
{
    m_angleLooking = atan2(m_pos.y - pos.y, m_pos.x - pos.x) * 180 / 3.141592f - 90.0f;
    m_playerSprite.setRotation(m_angleLooking);
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerSprite, states);
}

sf::Vector2f Player::getPosition() const
{
    return m_pos;
}
