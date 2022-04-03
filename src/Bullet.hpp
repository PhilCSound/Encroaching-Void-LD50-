#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

class Bullet : public sf::Drawable
{
public:
    Bullet(sf::Vector2f& pos, sf::Vector2f& m_vel, sf::Texture& text);
    void update(sf::Time elapTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2f getPos();
    bool isDead();
private:
    sf::Vector2f m_pos;
    sf::Vector2f m_vel;
    sf::Vector2f m_halfSize;
    sf::FloatRect m_hitBox;
    sf::Sprite m_sprite;
    bool m_isDead = false;
};
