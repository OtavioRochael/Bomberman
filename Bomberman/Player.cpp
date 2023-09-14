#include "Player.hpp"
#include <iostream>

Player::Player()
{
	isPlantingBomb = false;
	size = 32;
	shape.setPosition(20.f, 20.f);
	speed = 200.f;
	scale = 2.f;
	shape.scale(scale, scale);
	shape.setOrigin(size/2.f, size/2.f);

	InitAnimations();
}

Player::~Player()
{
}

void Player::Update(sf::Time& deltaTime)
{
	UpdateAnimations();
	animator->Update(deltaTime);
}

void Player::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Player::SetDirection(Direction dir)
{
	currentDirection = dir;
}

Direction Player::GetDirection()
{
	return currentDirection;
}

float Player::GetSpeed()
{
	return speed;
}

sf::Vector2f Player::GetPosition()
{
	return shape.getPosition();
}

void Player::SetPosition(float x, float y)
{
	shape.setPosition(x, y);
}

void Player::Reset()
{
	SetDirection(Direction::None);
	shape.setPosition(sf::Vector2f(spawnPosition.x * size, spawnPosition.y * size));
	speed = 5.f;
}

const bool Player::IsPlantingBomb() const
{
	return isPlantingBomb;
}

void Player::Move(const float x,const float y, sf::Time& deltaTime)
{
	shape.move(x * speed * deltaTime.asSeconds(), y * speed * deltaTime.asSeconds());
}

void Player::PlantBomb()
{
	animator->SwitchAnimation("PlantingBomb");
	//Instanciar bomba na posição
}

void Player::InitAnimations()
{
	animator = new Animator(shape);

	texture = AssetManager::GetTexture("Texture/BombermanSheet.png");
	shape.setTexture(texture);

	auto& idle = animator->CreateAnimation("Idle", "Texture/BombermanSheet.png", sf::seconds(0.25f), true);
	idle.AddFrames(sf::Vector2i(size * 0, size * 1), sf::Vector2i(size, size), 1);

	auto& walkRight = animator->CreateAnimation("WalkToRight", "Texture/BombermanSheet.png", sf::seconds(0.5f), true);
	walkRight.AddFrames(sf::Vector2i(size * 3, size * 1), sf::Vector2i(size, size), 5);

	auto& walkDown = animator->CreateAnimation("WalkToDown", "Texture/BombermanSheet.png", sf::seconds(0.5f), true);
	walkDown.AddFrames(sf::Vector2i(size * 1, size * 1), sf::Vector2i(size, size), 2);

	auto& walkUp = animator->CreateAnimation("WalkToUp", "Texture/BombermanSheet.png", sf::seconds(0.5f), true);
	walkUp.AddFrames(sf::Vector2i(size * 0, size * 2), sf::Vector2i(size, size), 3);

	auto& plantingBomb = animator->CreateAnimation("PlantingBomb", "Texture/BombermanSheet.png", sf::seconds(0.5f), false);
	plantingBomb.AddFrames(sf::Vector2i(size * 0, size * 7), sf::Vector2i(size, size), 1);
}

void Player::UpdateAnimations()
{
	std::string animation;
	shape.setScale(scale, scale);

	switch (currentDirection)
	{
	case Direction::None:
		animation = "Idle";
		break;
	case Direction::Up:
		animation = "WalkToUp";
		break;
	case Direction::Down:
		animation = "WalkToDown";
		break;
	case Direction::Left:
		shape.setScale(-scale, scale);
		animation = "WalkToRight";
		break;
	case Direction::Right:
		animation = "WalkToRight";
		break;
	}

	if(animation != animator->GetCurrentAnimationName())
		animator->SwitchAnimation(animation);
}
