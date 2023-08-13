#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#endif // DEBUG

int main_w()
{
	sf::Window window;
	sf::ContextSettings settings;
	window.create(sf::VideoMode(400, 400), "Hello SFML", sf::Style::Default, settings);

	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (std::size_t i = 0; i < modes.size(); ++i)
	{
		sf::VideoMode mode = modes[i];
		std::cout << "Mode #" << i << ": "
				  << mode.width << "x" << mode.height << " - "
				  << mode.bitsPerPixel << " bpp" << std::endl;
	}

	sf::Window window2(*modes.rbegin(), "Window2", sf::Style::Titlebar | sf::Style::Close);

	sf::Image image;
	if (image.loadFromFile("../Res/title.png"))
	{
		auto size = image.getSize();
		window.setIcon(size.x, size.y, image.getPixelsPtr());
	}
	window.setTitle("SFML Window");
	window.setPosition(sf::Vector2i(100, 100));
	window.setSize(sf::Vector2u(960, 640));

	window.display();
	window2.display();

	while (window.isOpen() || window2.isOpen())
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		while (window2.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
			{
				window2.close();
			}
		}
	}

	return 0;
}