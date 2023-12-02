#pragma once
#include "Window.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsedTime();
	void RestartClock();
private:
	AssetManager assetManager;

	Map* map;
	Window window;

	sf::Vector2u windowSize{window.GetWindowSize()};

	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time deltaTime;

	Player player;
};

