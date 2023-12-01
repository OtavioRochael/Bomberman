#include "Struture.hpp"
#include <ctime>

Structure::Structure(float posX, float posY, StrutureType type) : position(posX, posY), type(type)
{
	InitSprite();
}

Structure::~Structure()
{
}

sf::Sprite Structure::GetSprite()
{
	return sprite;
}

void Structure::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Structure::InitSprite()
{
	switch (type)
	{
	case Grass: {
		int chance = rand() % 100 + 1;
		if (chance < 75)
			texture = AssetManager::GetTexture("Texture/grass.png");
		else
			texture = AssetManager::GetTexture("Texture/grass1.png");
		break;
	}
	case DirtWall:
		texture = AssetManager::GetTexture("Texture/Brick.png");
		break;
	case MetalWall:
		texture = AssetManager::GetTexture("Texture/Stone.png");
		break;
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
}