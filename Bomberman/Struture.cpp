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
	int chance = (108237 % 100) + 1;
	switch (type)
	{
	case Grass: 
		if (chance < 75)
			texture = AssetManager::GetTexture("Texture/grass.png");
		else
			texture = AssetManager::GetTexture("Texture/grass1.png");
		break;
	case DirtWall:
		texture = AssetManager::GetTexture("Texture/Brick.png");
		break;
	case Stone:
		if (chance < 33)
			texture = AssetManager::GetTexture("Texture/stone1.png");
		else if(chance < 66)
			texture = AssetManager::GetTexture("Texture/stone2.png");
		else
			texture = AssetManager::GetTexture("Texture/stone3.png");
		
		break;
	case Box:
		texture = AssetManager::GetTexture("Texture/box.png");
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);
}