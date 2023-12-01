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
	void SetCollidable(bool isCollidable);
	sf::FloatRect GetGlobalBounds();

	bool IsAnimationPlayed();
	const bool GetCollidable() const { return isCollidable; }
private:
	sf::Sprite sprite;
	sf::Texture texture;

	Animator *animator;

	bool isCollidable{ false };
	bool animPlayed{ false };

	void InitAnimations();
};

