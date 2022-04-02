#include "InGameState.hpp"

void InGameState::OnEntry(Engine *eng)
{
    m_tgui.setTarget(eng->GetWindow());
    m_randomGenerator.seed(std::random_device{}());
    sf::Vector2u size = eng->GetWindow().getSize();
}

void InGameState::OnExit(Engine *eng)
{
}

void InGameState::Draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White); //Test
    sf::RenderStates rs;
    window.draw(m_lightMap, sf::BlendMultiply);
    m_tgui.draw();
}

void InGameState::Update(Engine *eng, sf::Time elapTime)
{
}

void InGameState::HandleEvent(sf::Event &event, sf::RenderWindow &window)
{
    m_tgui.handleEvent(event);
    sf::Vector2f mousePos;
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
            mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            m_lightMap.AddLight(mousePos, 30.0f);
            break;
        // Event here
        default:
            break;
    }
}

void InGameState::Pause()
{
}

void InGameState::Unpause()
{
}
