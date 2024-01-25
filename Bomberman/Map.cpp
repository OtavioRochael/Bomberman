#include "Map.hpp"

Map::Map(sf::Vector2i windowSize, int tileSize) : windowSize(windowSize), tileSize(tileSize)
{
	RestartClock();
	InitMap();
}

Map::~Map()
{
}


void Map::Render(sf::RenderWindow& window)
{
	for (int row = 0; row < mapSizeX / 2; ++row) {
		for (int col = 0; col < mapSizeY / 2; ++col) {
			mapGrass[row][col]->Render(window);
			map[row][col]->Render(window);
		}
	}
}

void Map::Remap(int idX, int idY)
{
	if (idX < 0 || idY < 0 || idX >= mapSizeX / 2.f || idY >= mapSizeY / 2.f)
		return;

	map[idX][idY] = new Structure(idX * tileSize, idY * tileSize, StrutureType::Grass);
}

void Map::SetMapChar(int posX, int posY, char c)
{
	if(posX < 0 || posY < 0 || posX >= mapSizeX/2.f|| posY >= mapSizeY/2.f)
		return;
	mapChar[posX][posY] = c;
}

void Map::ResetMap()
{
	mapChar = {
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
		{ '*', '-', '-', '+', '+', '+', '/', '+', '+', '+', '+', '*'},
		{ '*', '-', '/', '+', '/', '+', '+', '/', '+', '/', '+', '*'},
		{ '*', '+', '+', '+', '+', '+', '/', '+', '+', '+', '+', '*'},
		{ '*', '/', '+', '/', '+', '/', '+', '+', '+', '+', '/', '*'},
		{ '*', '+', '/', '+', '+', '+', '+', '+', '/', '+', '+', '*'},
		{ '*', '+', '+', '+', '/', '+', '+', '+', '+', '+', '+', '*'},
		{ '*', '+', '/', '/', '+', '+', '+', '+', '+', '/', '+', '*'},
		{ '*', '+', '+', '+', '+', '/', '+', '/', '+', '+', '+', '*'},
		{ '*', '+', '/', '+', '+', '/', '+', '+', '+', '/', '-', '*'},
		{ '*', '+', '+', '+', '/', '+', '+', '+', '/', '-', '-', '*'},
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
	};
}

char Map::GetMapChar(int posX, int posY)
{
	if(posX < 0 || posY < 0 || posX >= mapSizeX/2.f|| posY >= mapSizeY/2.f)
		return ' ';
	return mapChar[posX][posY];
}

void Map::InitMap()
{
	mapSizeX = windowSize.x / tileSize;
	mapSizeY = windowSize.y / tileSize;

	ResetMap();

	for (int i = 0; i < mapSizeX; i++) {
		map.push_back(std::vector<Structure*>());
		mapGrass.push_back(std::vector<Structure*>());
	}

	for (int i = 0; i < mapSizeX; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			map[i].reserve(j);
			mapGrass[i].reserve(j);
		}
	}

	for (int row = 0; row < mapSizeX / 2; row++) {
		for (int col = 0; col < mapSizeY / 2; col++) {
			mapGrass[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Grass));
			switch (mapChar[row][col])
			{
			case '-':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Grass));
				break;
			case '+':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Box));
				break;
			case '/':
				map[row].push_back(new Structure(row * tileSize, col * tileSize, StrutureType::Stone));
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

void Map::RestartClock()
{
	deltaTime = clock.restart();
}
