
#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "State.hpp"
#include <vector>

class State;

class Engine
{
public:
	Engine();
	~Engine();
	const bool IsRunning() const;
	void Update();
	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();
	sf::RenderWindow& GetWindow() { return m_window; }

private:
	void HandleInput();

	std::vector<State*> m_stackOfStates;


	sf::Clock m_clock;
	bool m_isRunning;
	sf::RenderWindow m_window;
};