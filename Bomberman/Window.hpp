#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window
{
public:
	Window(const std::string& title, const sf::Vector2u size);
	~Window();

	void BeginDraw();
	void Draw(sf::Drawable& drawable);
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();

	sf::Vector2u GetWindowSize();
	sf::RenderWindow* GetRenderWindow();

	void ToggleFullscreen();

private:
	void Setup(const std::string& title, const sf::Vector2u size);
	void Destroy();
	void Create();

	sf::View view;
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	sf::String windowTitle;

	bool isFullScreen;
	bool isDone;

};

