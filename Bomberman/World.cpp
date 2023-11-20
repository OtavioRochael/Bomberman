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

	for (int i = 0; i < 144; i++) {
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setScale(sf::Vector2f(1.f, 1.f));
		sprites.push_back(sprite);
	}

	int i = 0;

	for (int row = 0; row < 12; ++row) {
		for (int col = 0; col < 12; ++col) {
			switch (map[row][col])
			{
			case ',':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/grass2.png"));
				break;
			case '+':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/grass1.png"));
				break;
			case '-':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/grass.png"));
				break;
			case '*':
				sprites[i]->setTexture(AssetManager::GetTexture("Texture/wall.png"));
				break;
			default:
				sprites[i]->setColor(sf::Color::Black);
				break;
			}

			i++;
		}
	}
	
	RenderMap();
}

void World::RenderMap()
{
	int posX = sprites[0][0].getGlobalBounds().width * sprites[0][0].getScale().x;
	int posY = sprites[0][0].getGlobalBounds().height * sprites[0][0].getScale().y;
	int i = 0;

	for (int x = 0; x < 12; ++x) {
		for (int y = 0; y < 12; ++y) {
			sprites[i]->setPosition(sf::Vector2f(posY * y, posX * x));
			i++;
		}
	}
}
