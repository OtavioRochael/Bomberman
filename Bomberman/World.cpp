#include "World.hpp"

World::World(sf::Vector2u windowSize, int tileSize) : windowSize(windowSize), tileSize(tileSize)
{
	InitMap();
}

World::~World()
{
}

int World::GetBlockSize()
{
	return 0;
}

void World::Update(Player& player)
{
	sf::Vector2f playerPos = player.GetPosition();
}

void World::Render(sf::RenderWindow& window)
{
	for (auto sprite : sprites) {
		window.draw(*sprite);
	}
}

void World::InitMap()
{
	map += "************************\n";
	map += "************************\n";
	map += "*----------------------*\n";
	map += "*----------------------*\n";
	map += "*----------------------*\n";
	map += "*----------------------*\n";
	map += "*----------------------*\n";
	map += "*----------------------*\n";
	map += "************************\n";
	map += "************************\n";


	for (int i = 0; i < map.size(); i++) {
		sprites.push_back(new sf::Sprite());
		sprites.at(i)->setScale(2.0f, 2.0f);
	}

	int i = 0;
	for (auto c : map) {
		switch (c)
		{
		case '\n':
			break;
		case '*':
			sprites[i]->setTexture(AssetManager::GetTexture("Texture/brickTile.png"));
			break;
		case '-':
			break;
		}

		i++;
	}
	
	RenderMap();
}

void World::RenderMap()
{
	int y = 0;
	int x = 0;
	int posX = tileSize * sprites[0]->getScale().x;
	int posY = tileSize * sprites[0]->getScale().y;

	for (int i = 0; i < map.size(); i++) {

 		if (map[i] == '\n') {
			y++;
			x = -1;
		}

		sprites[i]->setPosition(sf::Vector2f(posX * x, posY * y));
		x++;
	}
}
