#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class World
{
public:
	World(sf::Vector2u windowSize);
	~World();

	int GetBlockSize();

	void Update(Player& player);

	void Render(sf::RenderWindow& window);
private:
	sf::Vector2u windowSize;
	sf::Vector2i bomb;
	int blockSize;

	sf::RectangleShape bounds[4];
};

