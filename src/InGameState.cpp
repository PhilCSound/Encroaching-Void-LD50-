#include "InGameState.hpp"

void InGameState::OnEntry(Engine *eng)
{
    m_tgui.setTarget(eng->GetWindow());
    m_tgui.loadWidgetsFromFile("resources/gui/voidui.txt");
    m_tgui.get<tgui::Button>("Replay")->onPress(&InGameState::Restart, this);
    m_randomGenerator.seed(std::random_device{}());
    sf::Vector2u size = eng->GetWindow().getSize();
    m_minimap.create(800, 600);
    m_enemyText.loadFromFile("resources/gfx/voidPlayer.png");
    m_bulletText.loadFromFile("resources/gfx/Bullet.png");
    m_noise.loadFromFile("resources/gfx/noiseTexture.png");
    m_noise.setRepeated(true);
    m_voidShader.loadFromFile("resources/shader/void.frag", sf::Shader::Fragment);
    m_voidShader.setUniform("noiseText", m_noise);
    m_voidShader.setUniform("texture", sf::Shader::CurrentTexture);
    CreateRandomEnemy();
    CreateRandomEnemy();
    CreateRandomEnemy();
}

void InGameState::OnExit(Engine *eng)
{
}

void InGameState::Draw(sf::RenderWindow &window)
{
    if(!m_player.isDead)
    {
    window.clear(sf::Color::White); //Test
    window.setView(m_camera.getView());
    window.draw(m_map);
    window.draw(m_player);
    for (auto& bull : m_playerBullets)
        window.draw(bull);
    window.draw(m_lightMap, &m_voidShader);
    for (auto& enemy : m_enemylist)
        window.draw(enemy);
    sf::View miniView;
    miniView.setSize(800, 600);
    miniView.setCenter(400,300);
    miniView.setViewport(sf::FloatRect(0.70f, 0.02f, 0.28f, 0.20f));
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
    m_tgui.get<tgui::ProgressBar>("Corrupt")->setValue(100 * m_player.GetHowCorrupt());
    if (m_player.canRightClick())
        m_tgui.get<tgui::ProgressBar>("Bless")->setValue(100);
    else
        m_tgui.get<tgui::ProgressBar>("Bless")->setValue(0);
    m_tgui.get<tgui::ProgressBar>("Fire")->setValue(100 * m_player.leftClickCD());
    }
    m_tgui.draw();
}

void InGameState::Update(Engine *eng, sf::Time elapTime)
{
    if (gameOver)
        return;
    if(m_player.isDead)
    {
        GAMEOVER();
        gameOver = true;
    }
    timeAlive += elapTime;
    enemySpawnTimer += elapTime;
    m_player.update(elapTime);
    UpdateShader(elapTime);
    if(enemySpawnTimer.asSeconds() > SPAWNTIME)
        CreateRandomEnemy();
    for(auto& b : m_playerBullets)
        b.update(elapTime);
    m_camera.setTargetPosition(m_player.getPosition());
    m_lightMap.update();
    CheckCollisions(elapTime);
    if(m_lightMap.checkCollision(m_player.getPosition(), 5))
        return;
    m_playerBullets.erase(std::remove_if(std::begin(m_playerBullets), std::end(m_playerBullets),
            [](Bullet& v) { return v.isDead; }), m_playerBullets.end());
    m_enemylist.erase(std::remove_if(std::begin(m_enemylist), std::end(m_enemylist),
            [](Enemy& v) { return v.isDead; }), m_enemylist.end());
}

void InGameState::HandleEvent(sf::Event &event, sf::RenderWindow &window)
{
    m_tgui.handleEvent(event);
    sf::Vector2f mousePos;
    sf::Vector2f dir;
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
            mousePos = window.mapPixelToCoords
                (sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            dir = m_player.fireDirection(mousePos);
            //LEFT CLICK
            if(event.mouseButton.button == sf::Mouse::Button::Left)
                FireBlaster(dir, 150.0f);
            else if (event.mouseButton.button == sf::Mouse::Button::Right) 
                FireCannon(mousePos, 40.0f);
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
        case sf::Event::LostFocus:
            m_player.ClearVelocity();
            break;
		case sf::Event::Resized:
            m_player.ClearVelocity();
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
    sf::RectangleShape s;
    s.setSize(sf::Vector2f(16, 16));
    s.setFillColor(sf::Color::Red);
    s.setOrigin(8,8);

    m_minimap.draw(m_lightMap);
    m_minimap.draw(m_player);
    for (auto& enemy : m_enemylist)
    {
        s.setPosition(enemy.getPosition());
        m_minimap.draw(s);
    }
    m_minimap.display();
    m_miniMapSprite.setTexture(m_minimap.getTexture());
}

void InGameState::CheckCollisions(sf::Time dt)
{
    sf::Vector2f vel = m_player.getVelocity() * dt.asSeconds();
    m_map.checkBounds(vel, m_player.getBounds());
    m_player.Move(vel);
    sf::Vector2f playerPos = m_player.getPosition();
    if (m_lightMap.checkCollision(playerPos, 0.0f))
        m_player.AddCorruption(0.5 * dt.asSeconds());

//Player bullet collisions with map then enemies
    for (auto& bull : m_playerBullets)
    {
        if(!bull.isDead)
        {   bool collide = false;
            for(auto& e : m_enemylist)
            {   
                if (e.isDead)
                    break;
                collide = bull.getHitbox().intersects(e.getBounds());
                if(collide)
                {
                    e.takeDamage();
                    if (e.isDead)
                        m_player.resetRightClick();
                    bull.isDead = true;
                    break;
                }
            }
            if (!collide)
                bull.isDead = m_map.checkBounds(sf::Vector2f(), bull.getHitbox());
        }
    }
//Enemy Collision
    for(auto& enemy : m_enemylist)
    {
        if (enemy.isDead)
            break;
        enemy.update();
        if(enemy.changeDir)
            enemy.AddVelocity(CreateRandomDirection());
        enemy.AttackInRadias(playerPos);
        sf::Vector2f ev = enemy.getVelocity();
        enemy.changeDir = m_map.checkBounds(ev, enemy.getBounds());
        enemy.Move(ev * dt.asSeconds());
        m_lightMap.AddVoid(enemy.getPosition(), 8);
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
        if (!m_player.getBounds().intersects(sf::FloatRect(x-40, y-40, 80, 80)))
            return sf::Vector2f(x, y);
    }
    return (sf::Vector2f(-30, -30));
}

void InGameState::CreateRandomEnemy()
{ 
    if (m_enemylist.size() >= 80)
        return;
    enemySpawnTimer = sf::Time::Zero;
    SPAWNTIME *= .95f;
    if (SPAWNTIME < .5)
        SPAWNTIME = .5;
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

void InGameState::FireBlaster(sf::Vector2f& dir, float ms)
{
    if (!m_player.canLeftClick())
        return;
    m_player.fireLeftClick();
    Bullet b = Bullet(m_player.getPosition() + dir * 8.0f, dir * ms, m_bulletText);
    m_playerBullets.push_back(b);
}

void InGameState::FireCannon(sf::Vector2f dir, float width)
{  
    if(!m_player.canRightClick())
        return;
    m_player.fireRightClick();
    m_lightMap.AddLight(dir, width);
    sf::CircleShape x;
    x.setPosition(dir);
    x.setRadius(width);
    sf::FloatRect zz = x.getGlobalBounds();
    zz.left = zz.left - width;
    zz.top = zz.top - width;
    zz.width = width*1.9f;
    zz.height = width*1.9f;

    for (auto& e : m_enemylist)
    {   
        if(e.isDead)
            break;
        else if (zz.contains(e.getPosition()))
        {
            e.takeDamage();
            if (e.isDead)
                m_player.resetRightClick();
        }
    }
}

void InGameState::UpdateShader(sf::Time dt)
{
    shaderTime += dt.asSeconds();
    if (shaderTime >= shaderTimeInSec)
    {
        m_voidShader.setUniform("iTime", 1.0f);
        shaderTime = 0.0f;
    }
    else
        m_voidShader.setUniform("iTime", shaderTime/shaderTimeInSec);

}

void InGameState::GAMEOVER()
{
    m_tgui.get<tgui::Group>("Group")->setVisible(true);
    m_tgui.get<tgui::ChatBox>("ChatBox")->addLine("Seconds survived: " + std::to_string((int)timeAlive.asSeconds()));
    m_tgui.get<tgui::ChatBox>("ChatBox")->addLine("Enemies Vanquished: " + std::to_string(m_player.enemiesKilled));
}

void InGameState::Restart()
{
    m_tgui.get<tgui::Group>("Group")->setVisible(false);
    m_player.reset();
    m_lightMap.restart();
    m_enemylist.clear();
    m_playerBullets.clear();
	gameOver = false;
    
	timeAlive = sf::Time::Zero;
	enemySpawnTimer = sf::Time::Zero;
	SPAWNTIME = 9.0f;

    CreateRandomEnemy();
    CreateRandomEnemy();
    CreateRandomEnemy();
}

