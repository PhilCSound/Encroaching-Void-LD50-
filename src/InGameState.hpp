#pragma once
#include "State.hpp"
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <random>

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
};