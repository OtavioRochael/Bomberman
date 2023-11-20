#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animator.hpp"
#include "Bomb.hpp"

enum class PlayerState { None, Up, Down, Left, Right, PlantingBomb };

class Player
{
public:
	Player();
	~Player();

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);

	void SetPlayerState(PlayerState dir);
	PlayerState GetDirection();
	sf::Vector2f GetPosition();
	float GetSpeed();

	void SetPosition(float x, float y);
	void PlantBomb();
	void PlantBombDelay(sf::Time deltaTime);
	bool CanPlantBomb();
	void SetColliding(bool isColliding);

	void Reset();

	void Move(float x, float y, sf::Time& deltaTime);
private:
	int lives;
	int speed;
	int bombs;
	int maxBombs;
	float bombDelay;
	float maxBombDelay;
	float scale;
	bool isColliding{ false };
	bool isPlantingBomb;

	std::vector<Bomb*> bombList;

	sf::Sprite shape;
	sf::Texture texture;
	int size;

	sf::Vector2u spawnPosition;
	PlayerState currentState;
	Animator *animator;

	void InitAnimations();
	void UpdateAnimations();
};

