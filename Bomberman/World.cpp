#include "World.hpp"

World::World(sf::Vector2u windowSize)
{
	blockSize = 64;

	//Bounds
	for (int i = 0; i < 4; i++) {
		bounds[i].setFillColor(sf::Color(150, 0, 0));

		if (!((i + 1) % 2)) {
			bounds[i].setSize(sf::Vector2f(windowSize.x, blockSize));
		}
		else {
			bounds[i].setSize(sf::Vector2f(blockSize, windowSize.y));
		}

		if (i < 2) {
			bounds[i].setPosition(0, 0);
		}
		else {
			bounds[i].setOrigin(bounds[i].getSize());
			bounds[i].setPosition(windowSize.x, windowSize.y);
		}
	}
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
	for (int i = 0; i < 4; i++) {
		window.draw(bounds[i]);
	}
}
