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
    window.draw(m_map);
    window.draw(m_player);
    window.draw(m_lightMap, sf::BlendMultiply);
    m_tgui.draw();
}

void InGameState::Update(Engine *eng, sf::Time elapTime)
{
    m_player.Move();
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
        case sf::Event::MouseMoved:
            mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            m_player.LookAt(mousePos);
            break;
        case sf::Event::KeyPressed:
            HandleKeyPresses(event.key.code);
            break;
        case sf::Event::KeyReleased:
            HandleKeyReleases(event.key.code);
            break;
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


///This is gonna be messy...
void InGameState::HandleKeyPresses(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::W:
        m_player.AddVelocity(sf::Vector2f(0, -1));
        break;
    case sf::Keyboard::A:
        m_player.AddVelocity(sf::Vector2f(-1, 0));
        break;
    case sf::Keyboard::S:
        m_player.AddVelocity(sf::Vector2f(0, 1));
        break;    
    case sf::Keyboard::D:
        m_player.AddVelocity(sf::Vector2f(1, 0));
        break;
    default:
        break;
    }
}

void InGameState::HandleKeyReleases(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::W:
        m_player.AddVelocity(-sf::Vector2f(0, -1));
        break;
    case sf::Keyboard::A:
        m_player.AddVelocity(-sf::Vector2f(-1, 0));
        break;
    case sf::Keyboard::S:
        m_player.AddVelocity(-sf::Vector2f(0, 1));
        break;    
    case sf::Keyboard::D:
        m_player.AddVelocity(-sf::Vector2f(1, 0));
        break;
    default:
        break;
    }
}
