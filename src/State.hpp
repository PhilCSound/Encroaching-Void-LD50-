#pragma once
#include "Engine.hpp"

class Engine;

class State {

public:
	virtual void OnEntry(Engine* eng) = 0;
	virtual void OnExit(Engine* eng) = 0;

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(Engine* eng, sf::Time elapTime) = 0;
	virtual void HandleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
	
	virtual void Pause() = 0;
	virtual void Unpause() = 0;
};