#include <SFML/Window.hpp>
#include <gl/glew.h>
#include <iostream>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

sf::Window window;
void dealEvent();

int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::VideoMode windowMode = sf::VideoMode(960, 640);

    window.create(windowMode, "Event");
    window.setPosition(sf::Vector2i((desktopMode.width - windowMode.width) / 2, (desktopMode.height - windowMode.height) / 2));

    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    glViewport(0, 0, windowMode.width, windowMode.height);
    window.display();

    window.setKeyRepeatEnabled(false);
    window.setJoystickThreshold(0.1);
    //sf::Mouse::setPosition(sf::Vector2i(100, 100));
    sf::Mouse::setPosition(sf::Vector2i(100, 100), window);

    while (window.isOpen())
    {
        dealEvent();
    }

    return 0;
}

void dealEvent()
{
    sf::Event evt;
    while (window.pollEvent(evt))
    {
        switch (evt.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::Resized:
            std::cout << "resize" << std::endl;
            glViewport(0, 0, evt.size.width, evt.size.height);
            window.display();
            break;
        case sf::Event::GainedFocus:
            std::cout << "gain focus" << std::endl;
            window.setSize(sf::Vector2u(960, 640));
            break;
        case sf::Event::LostFocus:
            std::cout << "lost focus" << std::endl;
            //window.setSize(sf::Vector2u(480, 320));
            break;
        case sf::Event::TextEntered:
            //std::cout << evt.text.unicode << std::endl;
            //if (evt.text.unicode < 128)
            //    std::cout << static_cast<char>(evt.text.unicode) << std::endl;
            break;
        case sf::Event::KeyPressed:
            std::cout << "key pressed" << std::endl;
            std::cout << evt.key.code << std::endl;
            std::cout << evt.key.control << std::endl;
            std::cout << evt.key.alt << std::endl;
            std::cout << evt.key.shift << std::endl;
            std::cout << evt.key.system << std::endl;
            break;
        case sf::Event::KeyReleased:
            std::cout << "key released" << std::endl;
            std::cout << evt.key.code << std::endl;
            std::cout << evt.key.control << std::endl;
            std::cout << evt.key.alt << std::endl;
            std::cout << evt.key.shift << std::endl;
            std::cout << evt.key.system << std::endl;
            break;
        case sf::Event::MouseButtonPressed:
            std::cout << evt.mouseButton.button << std::endl;
            std::cout << evt.mouseButton.x << std::endl;
            std::cout << evt.mouseButton.y << std::endl;
            break;
        case sf::Event::MouseWheelScrolled:
            if (evt.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                std::cout << "wheel type: horizontal" << std::endl;
            else if (evt.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                std::cout << "wheel type: vertical" << std::endl;
            std::cout << evt.mouseWheelScroll.delta << std::endl;
            std::cout << evt.mouseWheelScroll.x << ", " << evt.mouseWheelScroll.y << std::endl;
            break;
        case sf::Event::MouseMoved:
            std::cout << "on mouse move: " << evt.mouseMove.x << ", " << evt.mouseMove.y << std::endl;
            break;
        case sf::Event::MouseEntered:
            std::cout << "on mouse enter" << std::endl;
            break;
        case sf::Event::MouseLeft:
            std::cout << "on mouse leave" << std::endl;
            break;
        case sf::Event::JoystickConnected:
            std::cout << "joystick connect: " << evt.joystickConnect.joystickId << std::endl;
            break;
        case sf::Event::JoystickDisconnected:
            std::cout << "joystick connect: " << evt.joystickConnect.joystickId << std::endl;
            break;
        case sf::Event::JoystickButtonPressed:
            std::cout << evt.joystickButton.joystickId << ", " << evt.joystickButton.button << std::endl;
            break;
        case sf::Event::JoystickButtonReleased:
            std::cout << evt.joystickButton.joystickId << ", " << evt.joystickButton.button << std::endl;
            break;
        case sf::Event::JoystickMoved:
            std::cout << evt.joystickMove.joystickId << std::endl;
            std::cout << evt.joystickMove.axis << std::endl;
            std::cout << evt.joystickMove.position << std::endl;
        default:
            break;
        }
    }
}
