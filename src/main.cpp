#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
using namespace std;

// Constant acceleration applied every frame (downward force) #GRAVITY
const float gravity = 0.3f;

int main()
{
    // Create a window of size 800x600 with title
    sf::RenderWindow window(sf::VideoMode({1200, 600}), "Test Window");

    // Limit FPS to 60
    window.setFramerateLimit(60);

    // ===================== PHYSICS STATE =====================
    float radius = 50.0f;       // Radius of the circle
    float velocityX = 0.0f;     // Current horizontal speed of object
    float velocityY = 0.0f;     // Current vertical speed of the object
    float groundX = 0.0f;       // X-position of ground
    float groundY = 400.0f;     // Y-position of ground
    float prevY = 0.0f;         // store previous frame positionY of object
    float groundWidth = 800.0f; // length of ground
    float movementSpeed = 1.0f; // movement speed of object
    float friction = 0.85f;     // friction to slowdown object
    struct objectPosition {     // object structure
        float positionX;
        float positionY;
    } objCircle;

    // ===================== OBJECT SETUP =====================

    // Create a circular object (our "player")
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);

    // Initial position (top-left of bounding box)
    circle.setPosition({200, 200});

    // Create ground as a thin rectangle
    sf::RectangleShape rectangle({800, 5});
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition({groundX, groundY});

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

        bool withinGround = (objCircle.positionX + radius * 2) <= groundWidth;
        // Calculate bottom of circle (needed for collision with ground)
        float circleBottom = circle.getPosition().y + radius * 2;

        // Check if object is touching or below ground
        bool onGround = (circleBottom >= groundY) && (objCircle.positionX < groundWidth); //<-------------------need fixing

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
        //position of ground (for future use when ground is not straight)
        groundX = rectangle.getPosition().x;
        groundY = rectangle.getPosition().y;

        //position of object
        objCircle.positionX = circle.getPosition().x;
        objCircle.positionY = circle.getPosition().y;

        // Apply gravity (acceleration increases downward speed)
        velocityY += gravity;

        // reduce horizontal speed due to friction
        velocityX *= friction;

        // Move object based on current velocity
        circle.move({velocityX, velocityY});

        /*
        =======================================================
        COLLISION PHASE
        - Fix object if it intersects ground
        =======================================================
        */

        // Recalculate bottom after movement
        circleBottom = circle.getPosition().y + radius * 2;

        if (circleBottom >= groundY && objCircle.positionX < groundWidth && prevY + radius * 2 <= groundY)
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
        {
            velocityX += movementSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            velocityX -= movementSpeed;
        }

        /*
        =======================================================
        PHYSICS PHASE 2
        - update previous frame values
        =======================================================
        */
        prevY = objCircle.positionY;

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