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
    sf::Vector2f getVelocity() const;
    sf::Vector2f fireDirection(sf::Vector2f dir);
    void ClearVelocity();

private:
    float m_moveSpeed = 2.0f;
    sf::Vector2f m_pos { 300.0f, 300.0f };
    sf::Vector2f m_vel;
    sf::FloatRect m_hitbox;
    float m_angleLooking = 180.0f;
    sf::Texture m_playerText;
    sf::Sprite m_playerSprite;
};