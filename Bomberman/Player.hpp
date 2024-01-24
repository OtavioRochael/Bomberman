#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animator.hpp"
#include "Bomb.hpp"

enum class PlayerState { None, Up, Down, Left, Right, PlantingBomb, isDead };
enum class SideCollision { None, Left, Right, Up, Down, LeftDown, LeftUp, RightDown, RightUp };

class Player
{
public:
	Player(Map* map);
	~Player();

	void Update(sf::Time& deltaTime);
	void Render(sf::RenderWindow& window);

	void SetPlayerState(PlayerState dir);
	PlayerState GetDirection();
	PlayerState GetPlayerState();
	sf::Vector2f GetPosition();
	float GetSpeed();

	void SetPosition(float x, float y);
	void PlantBomb();
	void PlantBombDelay(sf::Time deltaTime);
	bool CanPlantBomb();
	const bool IsColliding();
	void SetColliding(bool isColliding);

	void Reset();

	void Move(float x, float y, sf::Time& deltaTime);
private:
	int speed;
	int bombs;
	int maxBombs;
	int bombRange;
	float bombDelay;
	float maxBombDelay;
	float scale;
	float collisionOffset{ 0.45f };
	bool isColliding{ false };
	bool leftColliding{ false };
	bool rightColliding{ false };
	bool upColliding{ false };
	bool downColliding{ false };
	bool isDead{ false };
	bool isPlantingBomb;

	std::vector<Bomb*> bombList;
	Map* map;

	sf::Sprite shape;
	sf::RectangleShape boxCollider;
	sf::Texture texture;
	int size;

	sf::Vector2u spawnPosition;
	PlayerState currentState;
	Animator *animator;

	void InitAnimations();
	void InitVariables();
	void InitShape();
	void BombManager(sf::Time& deltaTime);
	void UpdateAnimations();
	void InitBoxCollider();
	void CheckCollision(std::vector<Explosion*> explosions);
	void CheckCollisionWithBomb(std::vector<Bomb*> bombs);
	void CheckCollisionWithMap();
	void CollisionDetected(SideCollision side);
};

