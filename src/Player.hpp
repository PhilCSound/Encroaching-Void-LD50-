#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

class Player : public sf::Drawable
{
public:
    Player();
    void AddVelocity(sf::Vector2f& velocity);
    void Move(sf::Vector2f newVel);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void LookAt(sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void update(sf::Time deltaTime);
    float getRotation() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f fireDirection(sf::Vector2f dir);
    void ClearVelocity();
    void AddCorruption(float amt);
    float GetHowCorrupt();
    bool canRightClick();
    void resetRightClick();
    void fireRightClick();
    float leftClickCD();
    bool canLeftClick();
    void fireLeftClick();
    int enemiesKilled =0;
    bool isDead = false;
    void reset();
private:
    float m_moveSpeed = 100.0f;
    sf::Vector2f m_pos { 300.0f, 300.0f };
    sf::Vector2f m_vel;
    sf::FloatRect m_hitbox;
    float m_angleLooking = 180.0f;
    sf::Texture m_playerText;
    sf::Sprite m_playerSprite;
    float corruption = 0.0f;
    bool m_rightClick = true;
    float m_leftCoolDownTime = 0.5f;
    float m_leftTime = 0.5f;
};