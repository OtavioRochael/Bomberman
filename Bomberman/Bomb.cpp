#include "Bomb.hpp"

Bomb::Bomb(sf::Vector2f pos): position(pos)
{
	sprite.setOrigin(tileSize/2.f, tileSize/2.f);
	sprite.setScale(2.f,2.f);
	texture = AssetManager::GetTexture("Texture/Bomb1.png");
	sprite.setTexture(texture);
	SetRoundPositionToSpawn();
}

Bomb::~Bomb()
{
}

void Bomb::Update(sf::Time& deltaTime)
{
}

void Bomb::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Bomb::SetRoundPositionToSpawn()
{
	position.x = round(position.x / tileSize) * tileSize;
	position.y = round(position.y / tileSize) * tileSize;
	sprite.setPosition(position.x, position.y);
}
