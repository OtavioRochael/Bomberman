#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.hpp"

class Bomba
{
public:
	Bomba(sf::Vector2f pos);
	~Bomba();

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	int size;

	sf::Vector2f SetRoundPositionToSpawn();
};

