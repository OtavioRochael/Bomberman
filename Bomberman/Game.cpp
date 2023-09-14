#include "Game.hpp"
#include <iostream>

Game::Game() : window("Bomberman", sf::Vector2u(768, 768)), player(), world(sf::Vector2u(768,768))
{
}

Game::~Game()
{
}

void Game::HandleInput()
{
	player.SetDirection(Direction::None);

	//Player inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.SetDirection(Direction::Up);
		player.Move(0.f, -1.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.SetDirection(Direction::Down);
		player.Move(0.f, 1.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.SetDirection(Direction::Left);
		player.Move(-1.f, 0.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.SetDirection(Direction::Right);
		player.Move(1.f, 0.f, elapsedTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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
