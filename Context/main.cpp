#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#pragma comment(lib, "opengl32.lib")

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    sf::ContextSettings context;
    sf::Window window(sf::VideoMode(400, 400), "OpenGL Context", sf::Style::Default, context);

    glClearColor(1.0f, 0, 0, 1.0f);

    while (window.isOpen())
    {
        sf::Event evt;
        while (window.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (evt.type == sf::Event::Resized)
            {
                glViewport(0, 0, evt.size.width, evt.size.height);
            }
        }

        display();
        window.display();
    }

    return 0;
}