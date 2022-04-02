#include "Camera.hpp"


Camera::Camera()
{
    m_view.setSize(sf::Vector2f(400, 300));
}

void Camera::setTargetPosition(sf::Vector2f& pos)
{
    m_pos = pos;
    m_view.setCenter(m_pos);
}

const sf::View& Camera::getView() const
{
    return m_view;
}
