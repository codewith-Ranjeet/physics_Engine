#include <SFML/Graphics.hpp>
#include <optional>

// Constant acceleration applied every frame (downward force) #GRAVITY
const float gravity = 0.3f;

int main()
{
    // Create a window of size 800x600 with title
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");

    // Limit FPS to 60
    window.setFramerateLimit(60);

    // ===================== PHYSICS STATE =====================

    float velocityY = 0.0f; // Current vertical speed of the object
    float groundY = 500.0f; // Y-position of ground
    float radius = 50.0f;   // Radius of the circle

    // ===================== OBJECT SETUP =====================

    // Create a circular object (our "player")
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);

    // Initial position (top-left of bounding box)
    circle.setPosition({200, 200});

    // Create ground as a thin rectangle
    sf::RectangleShape rectangle({800, 5});
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition({0, 500});

    // ===================== MAIN LOOP =====================

    while (window.isOpen())
    {
        // -------- EVENT HANDLING (window close, etc.) --------
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        /*
        =======================================================
        INPUT PHASE
        - Read user input
        - Decide what changes should happen (e.g., jump)
        =======================================================
        */

        // Calculate bottom of circle (needed for collision with ground)
        float circleBottom = circle.getPosition().y + radius * 2;

        // Check if object is touching or below ground
        bool onGround = (circleBottom >= groundY);

        // Jump input (only allowed when on ground)
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
            onGround)
        {
            // Apply upward impulse (negative Y = up)
            velocityY = -8.0f;
        }

        /*
        =======================================================
        PHYSICS PHASE
        - Apply forces (gravity)
        - Update velocity
        - Update position
        =======================================================
        */

        // Apply gravity (acceleration increases downward speed)
        velocityY += gravity;

        // Move object based on current velocity
        circle.move({0, velocityY});

        /*
        =======================================================
        COLLISION PHASE
        - Fix object if it intersects ground
        =======================================================
        */

        // Recalculate bottom after movement
        circleBottom = circle.getPosition().y + radius * 2;

        if (circleBottom >= groundY)
        {
            // Snap object exactly onto ground (prevent sinking)
            circle.setPosition({circle.getPosition().x, groundY - radius * 2});
            // Stop downward velocity
            velocityY = 0;
        }

        /*
        =======================================================
        HORIZONTAL MOVEMENT (INPUT + DIRECT POSITION CHANGE)
        Note: This bypasses physics (need to be fixed using velocityX)
        =======================================================
        */

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            circle.move({2, 0}); // Move right

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            circle.move({-2, 0}); // Move left

        /*
        =======================================================
        RENDER PHASE
        - Clear previous frame
        - Draw objects
        - Display final frame
        =======================================================
        */

        window.clear(sf::Color::Black); // Clear screen with black

        window.draw(rectangle); // Draw ground
        window.draw(circle);    // Draw player (circle)

        window.display(); // Present frame to screen
    }

    return 0;
}