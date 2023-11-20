#include "Player.hpp"
#include <iostream>

Player::Player()
{
	maxBombs = 1;
	maxBombDelay = 2.f;
	bombDelay = maxBombDelay;
	bombs = 3;
	isPlantingBomb = false;
	size = 32;
	shape.setPosition(48.f, 48.f);
	speed = 200.f;
	scale = 1.5f;
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
	PlantBombDelay(deltaTime);
}

void Player::Render(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Player::SetPlayerState(PlayerState dir)
{
	currentState = dir;
}

PlayerState Player::GetDirection()
{
	return currentState;
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
	SetPlayerState(PlayerState::None);
	shape.setPosition(sf::Vector2f(spawnPosition.x * size, spawnPosition.y * size));
	speed = 10.f;
}

void Player::Move(const float x,const float y, sf::Time& deltaTime)
{
	shape.move(x * speed * deltaTime.asSeconds(), y * speed * deltaTime.asSeconds());
}

void Player::PlantBomb()
{
	if (CanPlantBomb()) {
		bombs--;
		std::cout << "Bombs: " << bombs << std::endl;
	}
}

bool Player::CanPlantBomb()
{
	if (bombs > 0 && bombDelay >= maxBombDelay) {
		bombDelay = 0;
		return true;
	}

	return false;
}

void Player::PlantBombDelay(sf::Time deltaTime)
{
	bombDelay += deltaTime.asSeconds();
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

	switch (currentState)
	{
	case PlayerState::None:
		animation = "Idle";
		break;
	case PlayerState::Up:
		animation = "WalkToUp";
		break;
	case PlayerState::Down:
		animation = "WalkToDown";
		break;
	case PlayerState::Left:
		shape.setScale(-scale, scale);
		animation = "WalkToRight";
		break;
	case PlayerState::Right:
		animation = "WalkToRight";
		break;
	case PlayerState::PlantingBomb:
		animation = "PlantingBomb";
		break;
	}

	if(animation != animator->GetCurrentAnimationName())
		animator->SwitchAnimation(animation);
}
