#include <SFML/Graphics.hpp>
#include <optional>
#include "physicsWorld.h"
using namespace std;

int main()
{
    // Create a window of size 800x600 with title
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Test Window");

    // Limit FPS to 60
    window.setFramerateLimit(60);

    // ---------- WORLD ----------
    physicsWorld world;

    // ---------- player ----------
    physicsObject player;
    player.x = 200.0f;
    player.y = 200.0f;
    player.height = 100.0f;
    player.width = 100.0f;

    // ---------- Ground ----------
    physicsObject ground;
    ground.x = 0.0f;
    ground.y = 500.0f;
    ground.height = 5.0f;
    ground.width = 800.0f;
    ground.isStatic = true;

    // Add to World
    world.objects.push_back(player);
    world.objects.push_back(ground);

    // SFML Shape Display
    // player
    sf::CircleShape playerShape(50);
    playerShape.setFillColor(sf::Color::Red);

    // Initial position of player (top-left of bounding box)
    playerShape.setPosition({player.x, player.y});

    // ground
    sf::RectangleShape groundShape({ground.width, ground.height});
    groundShape.setFillColor(sf::Color::Green);
    groundShape.setPosition({ground.x, ground.y});

    // ===================== MAIN LOOP =====================

    while (window.isOpen())
    {
        // -------- EVENT HANDLING (window close, etc.) --------
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // ---------- INPUT ----------

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            world.objects[0].velocityX += world.objects[0].movementSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            world.objects[0].velocityX -= world.objects[0].movementSpeed;
        }
        // Jump input (only allowed when on ground)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && world.objects[0].isGrounded))
        {
            // Apply upward impulse (negative Y = up)
            world.objects[0].velocityY = -8.0f;
        }

        // ---------- World Update ----------
        world.update();

        // ---------- SYNC RENDER ----------
        playerShape.setPosition({world.objects[0].x, world.objects[0].y});
        groundShape.setPosition({world.objects[1].x, world.objects[1].y});

        // ---------- RENDER ----------

        window.clear(sf::Color::Black); // Clear screen with black

        window.draw(groundShape); // Draw ground
        window.draw(playerShape); // Draw player (circle)

        window.display(); // Present frame to screen
    }

    return 0;
}