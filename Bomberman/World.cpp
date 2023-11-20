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

void World::Update()
{
}

void World::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < 144; i++) {
		if(sprites[i] != nullptr)
			window.draw(*sprites[i]);
	}
}

void World::CheckPlayerCollisions(Player& player)
{
	int playerXPosInGrid = player.GetPosition().x / tileSize;
	int playerYPosInGrid = player.GetPosition().y / tileSize;
}

void World::InitMap()
{
	map = {
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '*',},
		{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
	};

	for (int i = 0; i < 144; i++) {
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setScale(sf::Vector2f(4.f, 4.f));
		sprites.push_back(sprite);
	}

	int i = 0;

	for (int row = 0; row < 12; ++row) {
		for (int col = 0; col < 12; ++col) {
			switch (map[row][col])
			{
			case '\n':
				break;
			case '*':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/brickTile.png"));
				break;
			case '-':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/grass1.png"));
				sprites[i]->setScale(2.0f,2.0f);
				break;
			default:
				break;
			}

			i++;
		}
	}
	
	RenderMap();
}

void World::RenderMap()
{
	int posX = tileSize * sprites[0][0].getScale().x;
	int posY = tileSize * sprites[0][0].getScale().y;
	int i = 0;

	for (int x = 0; x < 12; ++x) {
		for (int y = 0; y < 12; ++y) {
			if (map[x][y] != '\n');
				sprites[i]->setPosition(sf::Vector2f(posY * y, posX * x));
			i++;
		}
	}
}
