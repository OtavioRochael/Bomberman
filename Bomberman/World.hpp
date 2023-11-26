#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class World
{
public:
	World(sf::Vector2u windowSize, int tileSize);
	~World();

	int GetBlockSize();

	void Update();

	void Render(sf::RenderWindow& window);

	char GetSpriteType(int x, int y);
private:
	Player player;

	sf::Vector2u windowSize;
	sf::Vector2i bomb;
	sf::Texture texture1;

	std::vector<std::vector<char>> map;
	std::vector<sf::Sprite*> sprites;
	
	int tileSize;

	void CheckPlayerCollisions(Player &player);
	void InitMap();
	void RenderMap();
};

