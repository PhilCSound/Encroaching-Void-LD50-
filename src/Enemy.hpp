#pragma once
#include "SFML/Graphics.hpp"

class Enemy : public sf::Drawable
{
public:
    Enemy(sf::Vector2f& pos, sf::Texture& text);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void AddVelocity(sf::Vector2f& velocity);
    void Move(sf::Vector2f newVel);
    void LookAt(sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getVelocity() const;
    

private:
    sf::Vector2f m_pos;
    sf::Vector2f m_vel;
    sf::FloatRect m_hitbox;
    sf::Sprite m_sprite;
    float m_angle = 0.0f;
    float m_moveSpeed = 2.0f;
};
