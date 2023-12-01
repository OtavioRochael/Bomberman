#include "Map.hpp"
#include "Map.hpp"

Map::Map(sf::Vector2i windowSize, int tileSize) : windowSize(windowSize), tileSize(tileSize)
{
	InitMap();
}

Map::~Map()
{
}


void Map::Render(sf::RenderWindow& window)
{
	for (int row = 0; row < mapSizeX / 2; ++row) {
		for (int col = 0; col < mapSizeY / 2; ++col) {
			map[row][col]->Render(window);
		}
	}
}

void Map::InitMap()
{
	mapSizeX = windowSize.x / tileSize;
	mapSizeY = windowSize.y / tileSize;

	mapChar = {
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',},
		{ '*', ',', '-', '-', '-', '-', '-', '-', '-', ',', '+', '*',},
		{ '*', '-', '-', '-', '+', '-', ',', '-', '-', '-', '-', '*',},
		{ '*', '+', '-', '-', '-', '-', '-', '-', '-', ',', '-', '*',},
		{ '*', '-', '-', ',', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '+', '-', '-', '-', '-', '-', '-', '+', '-', '*',},
		{ '*', '-', '-', '-', '-', '+', '-', '-', '-', '-', ',', '*',},
		{ '*', '-', '-', '+', '-', '-', '-', '-', '+', '-', '-', '*',},
		{ '*', ',', '-', '-', '-', '-', '+', '-', '-', '-', '-', '*',},
		{ '*', '-', ',', '-', '+', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', ',', '-', '-', '+', '*',},
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
	};

	for (int i = 0; i < mapSizeX; i++) {
		map.push_back(std::vector<Structure*>());
	}

	for (int i = 0; i < mapSizeX; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			map[i].reserve(j);
		}
	}

	for (int row = 0; row < mapSizeX/2; row++) {
		for (int col = 0; col < mapSizeY/2; col++) {
			switch (mapChar[row][col])
			{
			case ',':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Grass));
				break;
			case '-':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Grass));
				break;
			case '+':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Grass));
				break;
			case '*':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::DirtWall));
				break;
			default:
				break;
			}
		}
	}
}
