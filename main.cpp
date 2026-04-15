#include <SFML/Graphics.hpp>
#include <optional>

const float gravity = 0.3f;

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    window.setFramerateLimit(60);

    // gravity
    float velocityY = 0.0f;
    float groundY = 500.0f;
    float radius = 50.0f;

    // circle
    sf::CircleShape circle(radius);
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

        /*
        ===========================================================================INPUT======================================================================================
        */
        float circleBottom = circle.getPosition().y + radius * 2;
        bool onGround = (circleBottom >= groundY); // check if object on ground

        if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
              sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))) &&
            onGround)
        {
            velocityY = -8.0f; // jump impulse
        }

        /*
        =================================================================PHYSICS=========================================================================
        */

        velocityY += gravity; // acclerate
        circle.move({0, velocityY});

        circleBottom = circle.getPosition().y + radius * 2;
        //gravity
        if (circleBottom >= groundY)
        {
            circle.setPosition({circle.getPosition().x, groundY - radius * 2});
            velocityY = 0;
        }

        // Movement with keypress
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            circle.move({2, 0});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            circle.move({-2, 0});

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        //     circle.move({0, 0.2});

        /*
        ==============================================================================RENDER==========================================================================
        */
        window.clear(sf::Color::Black); // bgcolor of window
        window.draw(rectangle);         // ground
        window.draw(circle);            // test object (circle)

        window.display();
    }

    return 0;
}
