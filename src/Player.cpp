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

void Player::update(sf::Time deltaTime)
{
    corruption -= deltaTime.asSeconds() * .015f;
    m_leftTime += deltaTime.asSeconds();
    if (corruption < 0)
        corruption = 0.0f;
    if (m_leftTime > m_leftCoolDownTime)
        m_leftTime = m_leftCoolDownTime;
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

sf::Vector2f Player::fireDirection(sf::Vector2f dir)
{
    sf::Vector2f dist = dir - m_pos;
    float len = sqrt(dist.x * dist.x + dist.y * dist.y);
    dist.x /= len;
    dist.y /= len;
    return dist;
}

void Player::ClearVelocity()
{
    m_vel = sf::Vector2f();
}

float Player::getRotation() const
{
    return m_angleLooking;
}

void Player::AddCorruption(float amt)
{
    corruption += amt;
    if (corruption >= 1.0f)
        isDead = true;
}

float Player::GetHowCorrupt()
{
    return corruption;
}

bool Player::canRightClick()
{
    return m_rightClick;
}

void Player::fireRightClick()
{
    m_rightClick = false;
}

void Player::resetRightClick()
{
    m_rightClick = true;
    enemiesKilled+=1;
}

float Player::leftClickCD()
{
    return m_leftTime/m_leftCoolDownTime;
}

bool Player::canLeftClick()
{
    if(m_leftTime/m_leftCoolDownTime >= 1.0f)
        return true;
    else
        return false;
}

void Player::fireLeftClick()
{
    m_leftTime = 0.0f;
}

void Player::reset()
{
    m_pos = sf::Vector2f(300.0f, 300.0f );
    ClearVelocity();
    m_angleLooking = 180.0f;
    corruption = 0.0f;
    m_rightClick = true;
    m_leftCoolDownTime = 0.5f;
    m_leftTime = 0.5f;
    m_playerSprite.setOrigin(sf::Vector2f(m_playerText.getSize()) * 0.5f);
    m_playerSprite.setPosition(m_pos);
    m_hitbox = sf::FloatRect(m_pos.x -8, m_pos.y -8, 16.0f,16.0f);
    enemiesKilled =0;
    isDead = false;
}
