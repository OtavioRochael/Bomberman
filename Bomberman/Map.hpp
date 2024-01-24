#pragma once
#include "Struture.hpp"

class Map
{
public:
	Map(sf::Vector2i windowSize, int tileSize);
	~Map();

	void Render(sf::RenderWindow& window);
	void Remap(int idX, int idY);
	void SetMapChar(int posX, int posY, char c);
	void ResetMap();
	Structure* GetStructure(int idX, int idY) { return map[idX][idY]; }
	char GetMapChar(int posX, int posY);
private:
	std::vector<std::vector<Structure*>> mapGrass;
	std::vector<std::vector<Structure*>> map;
	std::vector<std::vector<char>> mapChar;

	sf::Vector2i windowSize;

	sf::Clock clock;
	sf::Time deltaTime;

	int tileSize;	
	int mapSizeX;
	int mapSizeY;

	void InitMap();
	void RestartClock();
};

