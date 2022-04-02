#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

class Player : public sf::Drawable
{
public:
    Player();
    void AddVelocity(sf::Vector2f& velocity);
    void Move();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void LookAt(sf::Vector2f& pos);
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f m_pos { 300.0f, 300.0f };
    sf::Vector2f m_vel;
    float m_angleLooking = 180.0f;
    sf::Texture m_playerText;
    sf::Sprite m_playerSprite;
};