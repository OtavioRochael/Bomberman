#include "Game.hpp"
#include <iostream>

Game::Game() : window("Bomberman", sf::Vector2u(768, 768)), player(), world(sf::Vector2u(768,768), 16)
{
}

Game::~Game()
{
}

void Game::HandleInput()
{
	player.SetPlayerState(PlayerState::None);

	//Player inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.SetPlayerState(PlayerState::Up);
		player.Move(0.f, -1.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.SetPlayerState(PlayerState::Down);
		player.Move(0.f, 1.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.SetPlayerState(PlayerState::Left);
		player.Move(-1.f, 0.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.SetPlayerState(PlayerState::Right);
		player.Move(1.f, 0.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		player.SetPlayerState(PlayerState::PlantingBomb); 
		player.PlantBomb();
	}
}

void Game::Update()
{
	window.Update();
	player.Update(elapsedTime);
}

void Game::Render()
{
	window.BeginDraw();
	world.Render(*window.GetRenderWindow());
	player.Render(*window.GetRenderWindow());
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
