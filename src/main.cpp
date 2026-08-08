#include <SFML/Graphics.hpp>

#include "physics/PhysicsWorld.h"
#include "input/InputHandler.h"
#include "rendering/Renderer.h"

int main()
{
    // ========== WINDOW ==========

    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Physics Engine");

    window.setFramerateLimit(60);

    // ========== SYSTEMS ==========

    PhysicsWorld world;
    InputHandler input;
    Renderer renderer(window);

    // ========== OBJECT SETUP ==========

    // ---------- Player ----------

    PhysicsObject player;

    player.x = 200.0f;
    player.y = 200.0f;

    player.collider.type = ColliderType::Circle;
    player.collider.radius = 50.0f;

    // ---------- Ground ----------

    PhysicsObject ground;

    ground.x = 0.0f;
    ground.y = 500.0f;

    ground.collider.type = ColliderType::Box;
    ground.collider.width = 800.0f;
    ground.collider.height = 5.0f;

    ground.isStatic = true;

    // ---------- Add objects to world ----------

    world.objects.push_back(player);
    world.objects.push_back(ground);

    // ========== MAIN LOOP ==========

    while (window.isOpen())
    {
        // ---------- EVENTS ----------

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // ---------- INPUT ----------

        float horizontalInput = input.getHorizontalInput();

        if (horizontalInput > 0)
        {
            world.objects[0].velocityX +=
                world.objects[0].movementSpeed;
        }

        if (horizontalInput < 0)
        {
            world.objects[0].velocityX -=
                world.objects[0].movementSpeed;
        }

        if (input.isJumpPressed() && world.objects[0].isGrounded)
        {
            world.objects[0].velocityY = -8.0f;
        }

        // ---------- PHYSICS ----------

        world.update();

        // ---------- RENDER ----------

        window.clear(sf::Color::Black);

        renderer.drawGround(world.objects[1]);
        renderer.drawPlayer(world.objects[0]);

        window.display();
    }

    return 0;
}