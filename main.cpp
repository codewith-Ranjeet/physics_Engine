#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    // sf::RenderWindow window(sf::VideoMode({800,600}), "My First Window");
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}