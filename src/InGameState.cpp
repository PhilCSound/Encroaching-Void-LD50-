#include "InGameState.hpp"

void InGameState::OnEntry(Engine *eng)
{
    m_tgui.setTarget(eng->GetWindow());
    m_randomGenerator.seed(std::random_device{}());
}

void InGameState::OnExit(Engine *eng)
{
}

void InGameState::Draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::Blue); //Test
    m_tgui.draw();
}

void InGameState::Update(Engine *eng, sf::Time elapTime)
{
}

void InGameState::HandleEvent(sf::Event &event, sf::RenderWindow &window)
{
    m_tgui.handleEvent(event);
    switch (event.type)
    {
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
