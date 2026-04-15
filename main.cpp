#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    // sf::RenderWindow window(sf::VideoMode({800,600}), "My First Window");
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");

    // gravity
    float velocityY = 0.01f;
    int groundY = 500;
    int radius = 50;

    // circle
    sf::CircleShape circle(50); // radius
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({200, 200});

    // ground
    sf::RectangleShape rectangle({800, 5});
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition({0, 500});

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black); // bgcolor of window

        window.draw(rectangle); // ground
        window.draw(circle);    // test object (circle)

        int circleBottom = circle.getPosition().y + radius * 2;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            circle.move({0.2, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            circle.move({-0.2, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            circle.move({0, -0.2});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            circle.move({0, 0.2});

        window.display();
    }

    return 0;
}
