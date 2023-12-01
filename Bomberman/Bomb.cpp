#include "Bomb.hpp"
#include <iostream>
#include "Map.hpp"

Bomb::Bomb(sf::Vector2f pos, int explosionRange): position(pos), explosionRange(explosionRange)
{
	SetRoundPositionToSpawn();
	sprite.setOrigin(tileSize/2.f, tileSize/2.f);
	sprite.setScale(2.f,2.f);
	texture = AssetManager::GetTexture("Texture/Bomb1.png");
	sprite.setTexture(texture);
	SetExplosionsPosition();
	InitAnimations();
}

Bomb::~Bomb()
{
}

void Bomb::Update(sf::Time& deltaTime)
{
	animator->Update(deltaTime);
	timer = timer + deltaTime.asSeconds();

	if (timer >= 5.f) {
		explode = true;
	}

	for (auto& explosion : explosions) {
		if (explode) {
			explosion->SetCollidable(true);
		}

		if (explode && !explosion->IsAnimationPlayed()) {
			explosion->PlayAnimation();
		}

		explosion->Update(deltaTime);
	}

	if (timer >= 5.5f)
	{
		isDone = true;
	}
}

void Bomb::Render(sf::RenderWindow& window)
{
	if(!explode)
		window.draw(sprite);
	
	if(explode)
	{
		for(auto& explosion : explosions)
		{
			explosion->Render(window);
		}
	}
}

void Bomb::InitAnimations()
{
	animator = new Animator(sprite);

	auto& idle = animator->CreateAnimation("Idle", "Texture/Bomb1.png", sf::seconds(5.f), false);
	
	idle.AddFrames(sf::Vector2i(tileSize * 0, tileSize * 0), sf::Vector2i(16, 16), 3);

	animator->SwitchAnimation("Idle");
}

void Bomb::SetRoundPositionToSpawn()
{
	position.x = round(position.x / tileSize) * tileSize;
	position.y = round(position.y / tileSize) * tileSize;
	sprite.setPosition(position.x, position.y);
}

void Bomb::SetExplosionsPosition()
{
	int posX = position.x - tileSize;
	int posY = position.y - tileSize;

	for(int i=1; i<=explosionRange; i++)
	{
		explosions.push_back(new Explosion(posX, posY));
		explosions.push_back(new Explosion(posX - i * tileSize, posY));
		explosions.push_back(new Explosion(posX + i * tileSize, posY));
		explosions.push_back(new Explosion(posX, posY + i * tileSize));
		explosions.push_back(new Explosion(posX, posY - i * tileSize));
	}
}
