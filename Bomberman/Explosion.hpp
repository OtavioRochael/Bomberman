#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.hpp"

class Explosion
{
public:
	Explosion(int posX, int posY);
	~Explosion();

	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow &window);
	void PlayAnimation();

	bool IsAnimationPlayed();
private:
	sf::Sprite sprite;
	sf::Texture texture;

	Animator *animator;

	bool animPlayed{ false };

	void InitAnimations();
};

