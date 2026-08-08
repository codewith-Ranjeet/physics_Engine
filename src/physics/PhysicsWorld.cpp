#include "PhysicsWorld.h"
#include <SFML/Graphics.hpp>

void PhysicsWorld::update()
{
    for (auto &obj : objects)
    {
        if (obj.isStatic)
            continue;

        // store previous position
        obj.prevY = obj.y;

        // apply gravity
        
        obj.velocityY += gravity;

        // apply friction
        obj.velocityX *= friction;

        // update position (postion using velocity)
        obj.x += obj.velocityX;
        obj.y += obj.velocityY;
    }

    // ---------- Collision (simple ground for now) ----------
    PhysicsObject &player = objects[0];
    PhysicsObject &ground = objects[1];

    player.movementSpeed = 1.0f; 
    player.isGrounded = false;

    float playerBottom = player.y + player.collider.radius;
    if (playerBottom >= ground.y && (player.prevY + player.collider.radius) <= ground.y && player.x < ground.collider.width)
    {
        player.y = ground.y - player.collider.radius;
        player.velocityY = 0;
        player.isGrounded = true;
    }
}