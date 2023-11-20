#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class World
{
public:
	World(sf::Vector2u windowSize, int tileSize);
	~World();

	int GetBlockSize();

	void Update(Player& player);

	void Render(sf::RenderWindow& window);
private:
	sf::Vector2u windowSize;
	sf::Vector2i bomb;
	sf::Texture texture1;

	std::string map;
	std::vector<sf::Sprite*> sprites;
	
	int tileSize;

	void InitMap();
	void RenderMap();
};

