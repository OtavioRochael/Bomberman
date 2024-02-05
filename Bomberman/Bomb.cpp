#include "Bomb.hpp"
#include <iostream>
#include "Map.hpp"

Bomb::Bomb(sf::Vector2f pos, int explosionRange, Map* map): position(pos), explosionRange(explosionRange), map(map)
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
    // Atualiza o estado do animator com base no tempo decorrido desde o último quadro
    animator->Update(deltaTime);

    // Incrementa o timer com o tempo decorrido desde o último quadro
    timer = timer + deltaTime.asSeconds();

    // Se o timer for maior ou igual a 5 segundos, a bomba é marcada para explodir
    if (timer >= 5.f) {
		explode = true;
    }

    // Loop que percorre todas as explosões da bomba
    for (auto& explosion : explosions) {
		// Se a bomba estiver marcada para explodir, a explosão é marcada como colidível
		if (explode) {
			explosion->SetCollidable(true);
		}

		// Se a bomba estiver marcada para explodir e a animação da explosão ainda não tiver sido reproduzida, a animação é iniciada
		if (explode && !explosion->IsAnimationPlayed()) {
			explosion->PlayAnimation();
		}

		// Atualiza o estado da explosão com base no tempo decorrido desde o último quadro
		explosion->Update(deltaTime);
    }

    // Se o timer for maior ou igual a 5.5 segundos, a bomba é marcada como concluída
    if (timer >= 5.25f)
    {
		for (auto ids : idsExplosions)
		{
			map->Remap(ids.x, ids.y);
		}

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

void Bomb::SetIsPassable(PLAYER_ID player_id, bool isPassable)
{
	if(player_id == PLAYER_ID::PLAYER1)
		this->isPassableP1 = isPassable;
	else
		this->isPassableP2 = isPassable;
}

bool Bomb::IsPassable(PLAYER_ID player_id)
{
	if(player_id == PLAYER_ID::PLAYER1)
		return isPassableP1;
	else
		return isPassableP2;
}

std::vector<Explosion*>& Bomb::GetExplosions()
{
	return explosions;
}

sf::FloatRect Bomb::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

sf::Vector2f Bomb::GetShapePosition()
{
	return sf::Vector2f(sprite.getPosition().x - tileSize, sprite.getPosition().y - tileSize);
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

	int idX = posX / tileSize;
	int idY = posY / tileSize;

	bool leftExplosion = false;
	bool rightExplosion = false;
	bool upExplosion = false;
	bool downExplosion = false;

	for (int i = 1; i <= explosionRange; i++)
	{
		if (map->GetMapChar(idX, idY) == '-') {
			explosions.push_back(new Explosion(posX, posY));
		}

		//Checa se a explosão deve ser criada na esquerda
		if (map->GetMapChar(idX - i, idY) == '-' && !leftExplosion)
			explosions.push_back(new Explosion(posX - i * tileSize, posY));
		else if (map->GetMapChar(idX - i, idY) == '+' && !leftExplosion) {
			explosions.push_back(new Explosion(posX - i * tileSize, posY));
			leftExplosion = true;
			map->SetMapChar(idX - i, idY, '-');
			idsExplosions.push_back(sf::Vector2i(idX - i, idY));
		}
		else if (map->GetMapChar(idX - i, idY) == '/' && !leftExplosion) {
			leftExplosion = true;
		}

		//Checa se a explosão deve ser criada na direita
		if (map->GetMapChar(idX + i, idY) == '-' && !rightExplosion)
			explosions.push_back(new Explosion(posX + i * tileSize, posY));
		else if (map->GetMapChar(idX + i, idY) == '+' && !rightExplosion) {
			explosions.push_back(new Explosion(posX + i * tileSize, posY));
			rightExplosion = true;
			map->SetMapChar(idX + i, idY, '-');
			idsExplosions.push_back(sf::Vector2i(idX + i, idY));
		}
		else if (map->GetMapChar(idX + i, idY) == '/' && !rightExplosion) {
			rightExplosion = true;
		}

		//Checa se a explosão deve ser criada em cima
		if (map->GetMapChar(idX, idY + i) == '-' && !downExplosion)
			explosions.push_back(new Explosion(posX, posY + i * tileSize));
		else if (map->GetMapChar(idX, idY + i) == '+' && !downExplosion) {
			explosions.push_back(new Explosion(posX, posY + i * tileSize));
			downExplosion = true;
			map->SetMapChar(idX, idY + i, '-');
			idsExplosions.push_back(sf::Vector2i(idX, idY + i));
		}
		else if (map->GetMapChar(idX, idY + i) == '/' && !downExplosion) {
			downExplosion = true;
		}

		//Checa se a explosão deve ser criada em baixo
		if (map->GetMapChar(idX, idY - i) == '-' && !upExplosion)
			explosions.push_back(new Explosion(posX, posY - i * tileSize));
		else if (map->GetMapChar(idX, idY - i) == '+' && !upExplosion) {
			explosions.push_back(new Explosion(posX, posY - i * tileSize));
			upExplosion = true;
			map->SetMapChar(idX, idY - i, '-');
			idsExplosions.push_back(sf::Vector2i(idX, idY - i));
		}
		else if (map->GetMapChar(idX, idY - i) == '/' && !upExplosion) {
			upExplosion = true;
		}
	}
}
