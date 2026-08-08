#include "Renderer.h"

Renderer::Renderer(sf::RenderWindow &window)
    : window(window)
{
}

void Renderer::drawPlayer(const PhysicsObject &player)
{
    if (player.collider.type == ColliderType::Circle)
    {
        sf::CircleShape playerShape(player.collider.radius);

        playerShape.setFillColor(sf::Color::Red);

        playerShape.setPosition({player.x, player.y});

        window.draw(playerShape);
    }
    else if (player.collider.type == ColliderType::Box)
    {
        sf::RectangleShape playerShape(sf::Vector2f(player.collider.width, player.collider.height));

        playerShape.setFillColor(sf::Color::Red);

        playerShape.setPosition({player.x, player.y});

        window.draw(playerShape);
    }
}

void Renderer::drawGround(const PhysicsObject &ground)
{
    sf::RectangleShape groundShape(sf::Vector2f(ground.collider.width, ground.collider.height));

    groundShape.setFillColor(sf::Color::Green);

    groundShape.setPosition({ground.x, ground.y});

    window.draw(groundShape);
}