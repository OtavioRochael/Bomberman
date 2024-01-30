#include "Player.hpp"

Player::Player(Map* map, std::vector<Bomb*>& enemyBombList, PLAYER_ID playerId) : map(map), enemyBombList(enemyBombList)
{
	this->SetPlayerId(playerId);
	InitVariables();
	InitAnimations();
	InitShape();
	InitBoxCollider();
}

Player::~Player()
{
	delete animator;
	for (auto bomb : bombList)
	{
		delete bomb;
	}
}

void Player::Update(sf::Time& deltaTime)
{
	UpdateAnimations();
	animator->Update(deltaTime);
	CheckCollisionWithMap();
	CheckCollisionWithBomb(this->bombList);
	CheckCollisionWithBomb(this->enemyBombList);
	PlantBombDelay(deltaTime);
	BombManager(deltaTime);
}

void Player::Render(sf::RenderWindow& window)
{
	for (auto bomb : bombList)
	{
		bomb->Render(window);
	}

	window.draw(boxCollider);
	window.draw(shape);
}

void Player::SetPlayerState(PlayerState dir)
{
	currentState = dir;
}

void Player::SetPlayerId(PLAYER_ID player_id)
{
	this->player_id = player_id;
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

std::vector<Bomb*>& Player::GetBombList()
{
	return bombList;
}

PlayerState Player::GetPlayerState()
{
	return this->currentState;
}

void Player::Move(const float x, const float y, sf::Time& deltaTime)
{
	if(!isColliding)
		shape.move(x * speed * deltaTime.asSeconds(), y * speed * deltaTime.asSeconds());
}

void Player::PlantBomb()
{
	if (CanPlantBomb()) {
		bombList.push_back(new Bomb(sf::Vector2f(this->GetPosition().x + 15, this->GetPosition().y + 20), bombRange, map));
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

const bool Player::IsColliding()
{
	return isColliding;
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

	if (animation != animator->GetCurrentAnimationName())
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
	for (auto& explosion : explosions)
	{
		if (boxCollider.getGlobalBounds().intersects(explosion->GetGlobalBounds()) && currentState != PlayerState::isDead && explosion->GetCollidable()) {
			currentState = PlayerState::isDead;
		}
	}
}

void Player::CheckCollisionWithMap()
{
	boxCollider.setPosition(this->GetPosition().x - 16 * 0.65, this->GetPosition().y - 16 * 0.75);

	int x = round(boxCollider.getPosition().x / size);
	int y = round(boxCollider.getPosition().y / size);

	Structure* structureR = map->GetStructure(x + 1, y);
	Structure* structureL = map->GetStructure(x - 1, y);
	Structure* structureU = map->GetStructure(x, y - 1);
	Structure* structureD = map->GetStructure(x, y + 1);
	Structure* structureRU = map->GetStructure(x + 1, y - 1);
	Structure* structureRD = map->GetStructure(x + 1, y + 1);
	Structure* structureLU = map->GetStructure(x - 1, y - 1);
	Structure* structureLD = map->GetStructure(x - 1, y + 1);
	
	if (structureR->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureR->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::Right);
		isColliding = true;
	}
	else if (structureL->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureL->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::Left);
		isColliding = true;
	}
	else if (structureD->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureD->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::Down);
		isColliding = true;
	}
	else if (structureU->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureU->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::Up);
		isColliding = true;
	}
	else if (structureLU->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureLU->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::LeftUp);
		isColliding = true;
	}
	else if (structureLD->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureLD->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::LeftDown);
		isColliding = true;
	}
	else if (structureRU->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureRU->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::RightUp);
		isColliding = true;
	}
	else if (structureRD->GetType() != StrutureType::Grass && this->boxCollider.getGlobalBounds().intersects(structureRD->GetSprite().getGlobalBounds())) {
		CollisionDetected(SideCollision::RightDown);
		isColliding = true;
	}
	else {
		CollisionDetected(SideCollision::None);
		isColliding = false;
	}
}

void Player::CollisionDetected(SideCollision side)
{
	if (side == SideCollision::Up)
		shape.setPosition(shape.getPosition().x, shape.getPosition().y + collisionOffset);
	if (side == SideCollision::Down)
		shape.setPosition(shape.getPosition().x, shape.getPosition().y - collisionOffset);
	if (side == SideCollision::Left)
		shape.setPosition(shape.getPosition().x + collisionOffset, shape.getPosition().y);
	if (side == SideCollision::Right)
		shape.setPosition(shape.getPosition().x - collisionOffset, shape.getPosition().y);
	if (side == SideCollision::LeftUp)
		shape.setPosition(shape.getPosition().x + collisionOffset, shape.getPosition().y + collisionOffset);
	if (side == SideCollision::LeftDown)
		shape.setPosition(shape.getPosition().x + collisionOffset, shape.getPosition().y - collisionOffset);
	if (side == SideCollision::RightUp)
		shape.setPosition(shape.getPosition().x - collisionOffset, shape.getPosition().y + collisionOffset);
	if (side == SideCollision::RightDown)
		shape.setPosition(shape.getPosition().x - collisionOffset, shape.getPosition().y - collisionOffset);
}

void Player::InitVariables()
{
	bombRange = 3;
	maxBombs = 10;
	maxBombDelay = 2.f;
	bombDelay = maxBombDelay;
	bombs = maxBombs;
	isPlantingBomb = false;
	size = 32;
	speed = 70.f;
	scale = 1.f;
}

void Player::InitBoxCollider()
{
	boxCollider = sf::RectangleShape();
	boxCollider.setSize(sf::Vector2f(size * 0.65, size * 0.75));
	boxCollider.setFillColor(sf::Color::Transparent);

	// Debug
	boxCollider.setOutlineThickness(2.f);
	boxCollider.setOutlineColor(sf::Color::Red);
}

void Player::InitShape()
{
	shape.setPosition(48.f, 48.f);
	shape.scale(scale, scale);
	shape.setOrigin(size / 2.f, size / 2.f);
}

void Player::CheckCollisionWithBomb(std::vector<Bomb*>& bombs)
{
	for (auto bomb : bombs)
	{
		if (bomb != NULL) {
			if (bomb->IsPassable(this->player_id) && boxCollider.getGlobalBounds().intersects(bomb->GetGlobalBounds()))
			{
				this->boxCollider.setOutlineColor(sf::Color::Green);
			}
			else {
				bomb->SetIsPassable(this->player_id, false);
				this->boxCollider.setOutlineColor(sf::Color::Red);
			}
			
			if (!bomb->IsPassable(this->player_id) ) {
				if (boxCollider.getGlobalBounds().intersects(bomb->GetGlobalBounds())) {
					sf::Vector2f dir = bomb->GetPosition() - boxCollider.getPosition();
					if (std::abs(dir.x) > std::abs(dir.y)) {
						if (dir.x > 0) {
							this->CollisionDetected(SideCollision::Right);
						}
						else {
							this->CollisionDetected(SideCollision::Left);
						}
						isColliding= true;
					}
					else {
						if (dir.y > 0) {
							this->CollisionDetected(SideCollision::Down);
						}

						else {
							this->CollisionDetected(SideCollision::Up);
						}
						isColliding = true;
					}
				}
				else {
				}
			}
		}
	}
}

void Player::BombManager(sf::Time& deltaTime)
{
	for (auto bomb : bombList)
	{
		if (bomb != NULL) {
			// Atualiza o estado da bomba com base no tempo decorrido desde o último quadro
			bomb->Update(deltaTime);

			if (bomb->IsExploded())
				CheckCollision(bomb->GetExplosions());

			if (bomb->IsDone())
			{
				bombList.erase(std::remove(bombList.begin(), bombList.end(), bomb), bombList.end());
				delete bomb;
			}
		}
	}
}
