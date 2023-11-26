#include "Window.hpp"

Window::Window(const std::string& title, const sf::Vector2u size)
{
	Setup(title, size);
}

Window::~Window()
{
}

void Window::BeginDraw()
{
	window.clear();
}

void Window::Draw(sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Window::EndDraw()
{
	window.display();
}

void Window::Update()
{
	sf::Event event;
	
	while (window.pollEvent(event)) {
		if (event.type == event.Closed) {
			isDone = true;
		}
		if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::F5) {
			ToggleFullscreen();
		}
	}
}

bool Window::IsDone()
{
	return isDone;
}

bool Window::IsFullscreen()
{
	return isFullScreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return windowSize;
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &window;
}

void Window::ToggleFullscreen()
{
	isFullScreen = !isFullScreen;
	Destroy();
	Create();
}

void Window::Setup(const std::string& title, const sf::Vector2u size)
{
	windowTitle = title;
	windowSize = size;
	isFullScreen = false;
	isDone = false;
	Create();
}

void Window::Destroy()
{
	window.close();
}

void Window::Create()
{
	auto style = isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;

	window.create({ windowSize.x, windowSize.y }, windowTitle, style);

	view = window.getView();
	view.setCenter(windowSize.x / 4, windowSize.y / 4);
	view.zoom(0.5f);
	window.setView(view);
}
