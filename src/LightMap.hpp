#pragma once
#include "SFML/Graphics.hpp"

class LightMap : public sf::Drawable
{
public:
    LightMap(unsigned int width = 800, unsigned int height = 600);
    void AddLight(sf::Vector2f& pos, float radias);
    void AddVoid(sf::Vector2f& pos, float radias);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool checkCollision(sf::Vector2f pos, int radias);
    void update();
private:
    sf::RenderTexture m_renderText;
    sf::Sprite m_sprite;
    sf::Image m_image;
    int frameCount = 0;
    int frameToUpdateImage = 12;

};
