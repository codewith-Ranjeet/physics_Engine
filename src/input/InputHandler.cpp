#include "InputHandler.h"
#include <SFML/Window/Keyboard.hpp>

float InputHandler::getHorizontalInput() const
{
    float input = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        input += 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        input -= 1.0f;
    }

    return input;
}

bool InputHandler::isJumpPressed() const
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
           sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
}