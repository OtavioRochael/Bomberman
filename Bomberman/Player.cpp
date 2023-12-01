#include "Player.hpp"

Player::Player()
{
	bombRange = 1;
	maxBombs = 10;
	maxBombDelay = 2.f;
	bombDelay = maxBombDelay;
	bombs = maxBombs;
	isPlantingBomb = false;
	size = 32;
	shape.setPosition(48.f, 48.f);
	speed = 70.f;
	scale = 1.f;
	shape.scale(scale, scale);

	InitAnimations();

	shape.setOrigin(size / 2.f, size / 2.f);
}

Player::~Player()
{
}

void Player::Update(sf::Time& deltaTime)
{
	UpdateAnimations();
	animator->Update(deltaTime);
	PlantBombDelay(deltaTime);
	
    for (auto bomb : bombList)
    {
        // Atualiza o estado da bomba com base no tempo decorrido desde o último quadro
        bomb->Update(deltaTime);

		if(bomb->IsExploded())
			CheckCollision(bomb->GetExplosions());

		if (bomb->IsDone())
		{
			bombList.erase(std::remove(bombList.begin(), bombList.end(), bomb), bombList.end());
			delete bomb;
		}
	}

}

void Player::Render(sf::RenderWindow& window)
{
	for(auto bomb : bombList)
	{
		bomb->Render(window);
	}

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
}

PlayerState Player::GetPlayerState()
{
	return this->currentState;
}

void Player::Move(const float x,const float y, sf::Time& deltaTime)
{
	if (!isColliding) {
		shape.move(x * speed * deltaTime.asSeconds(), y * speed * deltaTime.asSeconds());
	}
}

void Player::PlantBomb()
{
	if (CanPlantBomb()) {
		bombList.push_back(new Bomb(sf::Vector2f(this->GetPosition().x + 15, this->GetPosition().y + 20), bombRange));
		bombs--;
	}
}

bool Player::CanPlantBomb()
{
	if (bombs > 0 && bombDelay >= maxBombDelay && bombList.size() <= maxBombs) {
		bombDelay = 0;
		return true;
	}

	return false;
}

void Player::PlantBombDelay(sf::Time deltaTime)
{
	bombDelay += deltaTime.asSeconds();
}

void Player::SetColliding(bool isColliding)
{
	this->isColliding = isColliding;
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
	case PlayerState::isDead:
		animation = "Idle";
		break;
	}

	if(animation != animator->GetCurrentAnimationName())
		animator->SwitchAnimation(animation);
}

/**
 * @brief Verifica se o jogador colidiu com alguma explosão.
 *
 * Esta função verifica se a caixa de colisão do jogador intersecta com os limites globais de qualquer explosão.
 * Se uma colisão for detectada e o jogador não estiver já em um estado 'morto', o estado do jogador é definido como 'morto'.
 *
 * @param explosions Um vetor de ponteiros para objetos Explosion para verificar a colisão com o jogador.
 */
void Player::CheckCollision(std::vector<Explosion*> explosions)
{
	float offset = size / 2.75f;
	collisionBox = sf::FloatRect(shape.getGlobalBounds().left + offset, shape.getGlobalBounds().top + offset, offset / 2.f, offset / 2.f);

	for (auto& explosion : explosions)
	{
		if (collisionBox.intersects(explosion->GetGlobalBounds()) && currentState != PlayerState::isDead && explosion->GetCollidable()) {
			currentState = PlayerState::isDead;
		}
	}
}

