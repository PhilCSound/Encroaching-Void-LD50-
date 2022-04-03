#include "Player.hpp"

Player::Player()
{
    m_playerText.loadFromFile("resources/gfx/newPlayer.png");
    m_playerSprite.setTexture(m_playerText);
    m_playerSprite.setOrigin(sf::Vector2f(m_playerText.getSize()) * 0.5f);
    m_playerSprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos.x -8, m_pos.y -8, 16.0f,16.0f);
}

void Player::AddVelocity(sf::Vector2f& velocity)
{
    m_vel += velocity;
}

void Player::Move(sf::Vector2f newVel)
{   
    m_pos += newVel;
    m_playerSprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos - sf::Vector2f(8,8), sf::Vector2f(16, 16));
}

void Player::LookAt(sf::Vector2f& pos)
{
    m_angleLooking = atan2(m_pos.y - pos.y, m_pos.x - pos.x) * 180 / 3.141592f - 90.0f;
    m_playerSprite.setRotation(m_angleLooking);
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerSprite, states);
    /*sf::RectangleShape x;
    x.setSize(sf::Vector2f(16,16));
    x.setPosition(m_hitbox.left, m_hitbox.top);
    x.setFillColor(sf::Color::Transparent);
    x.setOutlineColor(sf::Color::Yellow);
    x.setOutlineThickness(-5.0f);
    target.draw(x);
    */
}

sf::Vector2f Player::getPosition() const
{
    return m_pos;
}

sf::FloatRect Player::getBounds() const
{
    return m_hitbox;
}

sf::Vector2f Player::getVelocity() const
{
    float invSqrt2 = 0.707106f;
    if (m_vel.x != 0.0f && m_vel.y != 0.0f)
        return m_vel * invSqrt2 * m_moveSpeed;
    return m_vel * m_moveSpeed;
}
