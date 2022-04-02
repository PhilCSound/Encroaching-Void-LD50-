#pragma once
#include "SFML/Graphics.hpp"

class Camera
{

public:
    Camera();
    void setTargetPosition(sf::Vector2f& pos);
    const sf::View& getView() const;
private:
    sf::View m_view;
    sf::Vector2f m_pos;
    sf::Vector2f m_targetPos;
};
