#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f& pos, sf::Texture& text)
    : m_pos(pos)
{
    m_sprite.setTexture(text);
    m_sprite.setRotation(m_angle);
    m_sprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos.x -8, m_pos.y -8, 16.0f,16.0f);

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}


void Enemy::AddVelocity(sf::Vector2f& velocity)
{
    m_vel += velocity;
}

void Enemy::Move(sf::Vector2f newVel)
{   
    m_pos += newVel;
    m_sprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos - sf::Vector2f(8,8), sf::Vector2f(16, 16));
}

void Enemy::LookAt(sf::Vector2f& pos)
{
    m_angle = atan2(m_pos.y - pos.y, m_pos.x - pos.x) * 180 / 3.141592f - 90.0f;
    m_sprite.setRotation(m_angle);
}

sf::Vector2f Enemy::getPosition() const
{
    return m_pos;
}

sf::FloatRect Enemy::getBounds() const
{
    return m_hitbox;
}

sf::Vector2f Enemy::getVelocity() const
{
    float invSqrt2 = 0.707106f;
    if (m_vel.x != 0.0f && m_vel.y != 0.0f)
        return m_vel * invSqrt2 * m_moveSpeed;
    return m_vel * m_moveSpeed;
}
