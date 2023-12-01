#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.hpp"
#include "Explosion.hpp"

class Bomb
{
public:
	Bomb(sf::Vector2f pos, int explosionRange);
	~Bomb();

	const bool IsExploded() const { return explode; }

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);

	bool IsDone() { return isDone; }

	std::vector<Explosion*>& GetExplosions();
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;

	std::vector<Explosion*> explosions;

	float timer;
	int explosionRange;

	bool explode{ false };
	bool animPlayed{false };
	bool isDone{ false };

	Animator *animator;

	int tileSize{ 32 };

	void InitAnimations();
	void SetRoundPositionToSpawn();
	void SetExplosionsPosition();
};

