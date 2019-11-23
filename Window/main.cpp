#include <SFML/Window.hpp>
#include <iostream>

int main()
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

	sf::Window window2(modes[0], "Window2", sf::Style::Fullscreen);

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