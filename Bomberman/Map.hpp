#pragma once
#include "Struture.hpp"

class Map
{
public:
	Map(sf::Vector2i windowSize, int tileSize);
	~Map();

	void Render(sf::RenderWindow& window);
private:
	std::vector<std::vector<Structure*>> map;
	std::vector<std::vector<char>> mapChar;

	sf::Vector2i windowSize;
	int tileSize;	
	int mapSizeX;
	int mapSizeY;

	void InitMap();
};

