#include "Game.hpp"
#include <iostream>

Game::Game() : window("Bomberman", sf::Vector2u(768, 768)), player1(map), player2(map), map(new Map(sf::Vector2i(768, 768), 32))
{
	elapsedTime = clock.restart();
}

Game::~Game()
{
}

void Game::HandleInput()
{
	if (player1.GetPlayerState() != PlayerState::isDead) {
		player1.SetPlayerState(PlayerState::None);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player1.SetPlayerState(PlayerState::Up);
			player1.Move(0.f, -1.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player1.SetPlayerState(PlayerState::Down);
			player1.Move(0.f, 1.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player1.SetPlayerState(PlayerState::Left);
			player1.Move(-1.f, 0.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player1.SetPlayerState(PlayerState::Right);
			player1.Move(1.f, 0.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player1.SetPlayerState(PlayerState::PlantingBomb);
			player1.PlantBomb();
		}
	}

	if (player2.GetPlayerState() != PlayerState::isDead) {
		player2.SetPlayerState(PlayerState::None);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player2.SetPlayerState(PlayerState::Up);
			player2.Move(0.f, -1.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player2.SetPlayerState(PlayerState::Down);
			player2.Move(0.f, 1.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player2.SetPlayerState(PlayerState::Left);
			player2.Move(-1.f, 0.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player2.SetPlayerState(PlayerState::Right);
			player2.Move(1.f, 0.f, elapsedTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			player2.SetPlayerState(PlayerState::PlantingBomb);
			player2.PlantBomb();
		}
	}
}

void Game::Update()
{
	window.Update();

	player1.Update(elapsedTime);
	player2.Update(elapsedTime);
}

void Game::Render()
{
	window.BeginDraw();
	map->Render(*window.GetRenderWindow());
	player1.Render(*window.GetRenderWindow());
	player2.Render(*window.GetRenderWindow());
	window.EndDraw();
}

Window* Game::GetWindow()
{
	return &window;
}

sf::Time Game::GetElapsedTime()
{
	return elapsedTime;
}

void Game::RestartClock()
{
	elapsedTime = clock.restart();
}
