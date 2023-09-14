#pragma once
#include <SFML/Graphics.hpp>
#include "Animator.hpp"

enum class Direction { None, Up, Down, Left, Right };
enum class State {Alive, Dead};

class Player
{
public:
	Player();
	~Player();

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);

	void SetDirection(Direction dir);
	Direction GetDirection();
	sf::Vector2f GetPosition();
	float GetSpeed();
	const bool IsPlantingBomb() const;

	void SetPosition(float x, float y);
	void PlantBomb();

	void Reset();

	void Move(float x, float y, sf::Time& deltaTime);
private:
	int lives;
	int speed;
	int bombs;
	float scale;
	bool isPlantingBomb;

	sf::Sprite shape;
	sf::Texture texture;
	int size; //Graphics size

	sf::Vector2u spawnPosition;
	Direction currentDirection;
	Animator *animator;

	void InitAnimations();
	void UpdateAnimations();
};

