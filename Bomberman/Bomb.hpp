#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.hpp"

class Bomb
{
public:
	Bomb(sf::Vector2f pos);
	~Bomb();

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	int tileSize{ 32 };

	void SetRoundPositionToSpawn();
};

