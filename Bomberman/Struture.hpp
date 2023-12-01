#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

enum StrutureType
{
	Box,
	Grass,
	DirtWall,
	Stone
};

class Structure
{
public:
	Structure(float posX, float posY, StrutureType type);
	~Structure();

	sf::Sprite GetSprite();
	void Render(sf::RenderWindow& window);
private:
	StrutureType type;
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;

	void InitSprite();
};

