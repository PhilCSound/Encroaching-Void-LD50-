#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include "LightMap.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class InGameState : public State
{
public:
	void OnEntry(Engine * eng) override;
	void OnExit(Engine* eng) override;

	void Draw(sf::RenderWindow & window) override;
	void Update(Engine * eng, sf::Time elapTime) override;
	void HandleEvent(sf::Event& event, sf::RenderWindow & window) override;

	void Pause() override;
	void Unpause() override;

private:
	//For Randomizing data.
	std::mt19937 m_randomGenerator;
	//TGUI
	tgui::GuiSFML m_tgui;
	//LightMap
	LightMap m_lightMap;
	//Player
	Player m_player;
	//Map
	Map m_map;
	//Camera
	Camera m_camera;
	//Minimap
	sf::RenderTexture m_minimap;
	sf::Sprite m_miniMapSprite; 
	//Enemys
	std::vector<Enemy> m_enemylist;
	sf::Texture m_enemyText;
	//Bulletlist
	sf::Texture m_bulletText;
	std::vector<Bullet> m_playerBullets;
	//Timers
	sf::Time timeAlive;
	sf::Time enemySpawnTimer;
	float SPAWNTIME = 9.0f;
    sf::RectangleShape s;
	bool m_drawCannonBlast = false;

	///
	//	Member Functions
	///
	void HandleKeyPresses(sf::Keyboard::Key key);
	void HandleKeyReleases(sf::Keyboard::Key key);
	void DrawToMinimap();
	void CheckCollisions(sf::Time dt);
	sf::Vector2f RandomPointNotNearPlayer();
	void CreateRandomEnemy();
	sf::Vector2f CreateRandomDirection();
	void FireBlaster(sf::Vector2f& direction, float mSpeed);
	void FireCannon(sf::Vector2f direction, float mWidth);
};