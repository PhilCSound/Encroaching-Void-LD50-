#include "InGameState.hpp"

void InGameState::OnEntry(Engine *eng)
{
    m_tgui.setTarget(eng->GetWindow());
    m_randomGenerator.seed(std::random_device{}());
    sf::Vector2u size = eng->GetWindow().getSize();
    m_minimap.create(800, 600);
    m_enemyText.loadFromFile("resources/gfx/voidPlayer.png");
    CreateRandomEnemy();
    CreateRandomEnemy();
    CreateRandomEnemy();
}

void InGameState::OnExit(Engine *eng)
{
}

void InGameState::Draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White); //Test
    window.setView(m_camera.getView());
    window.draw(m_map);
    window.draw(m_player);
    window.draw(m_lightMap);
    for (auto& enemy : m_enemylist)
        window.draw(enemy);
    sf::View miniView;
    miniView.setSize(800, 600);
    miniView.setCenter(400,300);
    miniView.setViewport(sf::FloatRect(0.7f, 0.05f, 0.25f, 0.25f));
    sf::RectangleShape CameraBorder;
    DrawToMinimap();
    CameraBorder.setFillColor(sf::Color::Transparent);
    CameraBorder.setOutlineColor(sf::Color::White);
    CameraBorder.setOutlineThickness(-5.0f);
    CameraBorder.setSize(sf::Vector2f(800, 600));
    window.setView(miniView);
    window.draw(m_miniMapSprite);
    window.draw(CameraBorder);
    window.setView(m_camera.getView());

    m_tgui.draw();
}

void InGameState::Update(Engine *eng, sf::Time elapTime)
{
    timeAlive += elapTime;
    enemySpawnTimer += elapTime;
    if(enemySpawnTimer.asSeconds() > SPAWNTIME)
        CreateRandomEnemy();
    m_camera.setTargetPosition(m_player.getPosition());
    m_lightMap.update();
    CheckCollisions();
    if(m_lightMap.checkCollision(m_player.getPosition(), 5))
        return;
}

void InGameState::HandleEvent(sf::Event &event, sf::RenderWindow &window)
{
    m_tgui.handleEvent(event);
    sf::Vector2f mousePos;
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
            mousePos = window.mapPixelToCoords
                (sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            m_lightMap.AddLight(mousePos, 30.0f);
            break;
        case sf::Event::MouseMoved:
            mousePos = window.mapPixelToCoords
                (sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
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

void InGameState::DrawToMinimap()
{
    m_minimap.clear(); //Test
    m_minimap.draw(m_map);
    m_minimap.draw(m_player);
    for (auto& enemy : m_enemylist)
        m_minimap.draw(enemy);
    m_minimap.draw(m_lightMap);
    m_minimap.display();
    m_miniMapSprite.setTexture(m_minimap.getTexture());
}

void InGameState::CheckCollisions()
{
    sf::Vector2f vel = m_player.getVelocity();
    m_map.checkBounds(vel, m_player.getBounds());
    m_player.Move(vel);
    sf::Vector2f playerPos = m_player.getPosition();

    for(auto& enemy : m_enemylist)
    {
        enemy.update();
        if(enemy.changeDir)
            enemy.AddVelocity(CreateRandomDirection());
        enemy.AttackInRadias(playerPos);
        sf::Vector2f ev = enemy.getVelocity();
        enemy.changeDir = m_map.checkBounds(ev, enemy.getBounds());
        enemy.Move(ev);
        m_lightMap.AddLight(enemy.getPosition(), 8);
    }
}

sf::Vector2f InGameState::RandomPointNotNearPlayer()
{
    for (int i = 0; i < 8; i++)
    {
        std::uniform_int_distribution<> xdist(8,792);
        std::uniform_int_distribution<> ydist(8,592);
        
        float x;
        float y;
        x = xdist(m_randomGenerator);
        y = ydist(m_randomGenerator);
        if (!m_player.getBounds().intersects(sf::FloatRect(x-8, y-8, 16, 16)))
            return sf::Vector2f(x, y);
    }
    return (sf::Vector2f(-30, -30));
}

void InGameState::CreateRandomEnemy()
{
    enemySpawnTimer = sf::Time::Zero;
    SPAWNTIME *= .98f;
    sf::Vector2f p = RandomPointNotNearPlayer();
    if(p.x < 0 || p.y < 0)
        return;
    else
        m_enemylist.push_back(Enemy(p, m_enemyText));    
}

sf::Vector2f InGameState::CreateRandomDirection()
{
    std::uniform_int_distribution<> dist(0,7);
    int dir = dist(m_randomGenerator);
    switch (dir)
    {
        case 0:
            return sf::Vector2f(0, -1);
        case 1:
            return sf::Vector2f(1, -1);
        case 2:
            return sf::Vector2f(1, 0);
        case 3:
            return sf::Vector2f(1, 1);
        case 4:
            return sf::Vector2f(0, 1);
        case 5:
            return sf::Vector2f(-1, 1);
        case 6:
            return sf::Vector2f(-1, 0);
        case 7:
            return sf::Vector2f(-1, -1);
        default:
            return sf::Vector2f(0,0);
    }
}
