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
    float invSqrt2 = 0.707106f;
    if (m_vel.x != 0.0f && m_vel.y != 0.0f)
        m_pos += m_vel * invSqrt2 * m_moveSpeed;
    else
        m_pos += m_vel * m_moveSpeed;
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
