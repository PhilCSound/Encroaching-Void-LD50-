#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f& pos, sf::Texture& text)
    : m_pos(pos)
{
    m_sprite.setTexture(text);
    m_sprite.setRotation(m_angle);
    m_sprite.setOrigin(sf::Vector2f(text.getSize()) * 0.5f);
    m_sprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos.x -8, m_pos.y -8, 16.0f,16.0f);

}

void Enemy::update()
{
    ++m_frameCount;
    if (m_tookDamage)
        m_tookDamage = false;
    else
        m_sprite.setColor(sf::Color::White);
    if (m_frameCount < m_changeDirFrame)
        return;
    m_frameCount = 0;
    changeDir = true;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite);
}


void Enemy::AddVelocity(sf::Vector2f& velocity)
{
    changeDir = false;
    m_vel = velocity;
    LookAt(m_pos + velocity);
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

void Enemy::AttackInRadias(sf::Vector2f& pos)
{
    if (pos.x > m_pos.x + ATTACK_RADIAS || pos.x < m_pos.x - ATTACK_RADIAS)
        return;
    if (pos.y > m_pos.y + ATTACK_RADIAS || pos.y < m_pos.y - ATTACK_RADIAS)
        return;
    sf::Vector2f dist = pos - m_pos;
    float len = sqrt(dist.x * dist.x + dist.y * dist.y);
    dist.x /= len;
    dist.y /= len;
    //Move in direction.
    AddVelocity(dist);
}

void Enemy::takeDamage()
{
    health -= 1;
    m_tookDamage = true;
    m_sprite.setColor(sf::Color::Red);
    if (health <= 0)
        isDead = true;
}
