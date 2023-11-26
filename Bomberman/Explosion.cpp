#include "Explosion.hpp"

Explosion::Explosion(int posX, int posY)
{
	sprite.setPosition(posX, posY);
	InitAnimations();
}

Explosion::~Explosion()
{
}

void Explosion::Update(sf::Time deltaTime)
{
	animator->Update(deltaTime);
}

void Explosion::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Explosion::PlayAnimation()
{	
	animator->SwitchAnimation("Explosion");
	animPlayed = true;
}

bool Explosion::IsAnimationPlayed()
{
	return animPlayed;
}

void Explosion::InitAnimations()
{
	animator = new Animator(sprite);
	auto& explosion = animator->CreateAnimation("Explosion", "Texture/explosion.png", sf::seconds(.5f), false);
	explosion.AddFrames(sf::Vector2i(0,0), sf::Vector2i(32,32), 9);
}
