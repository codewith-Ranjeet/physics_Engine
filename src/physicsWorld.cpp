#include "physicsWorld.h"
#include <SFML/Graphics.hpp>

void physicsWorld::update()
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
    physicsObject &player = objects[0];
    physicsObject &ground = objects[1];

    player.movementSpeed = 1.0f; 
    player.isGrounded = false;

    float playerBottom = player.y + player.height;
    if (playerBottom >= ground.y && (player.prevY + player.height) <= ground.y && player.x < ground.width)
    {
        player.y = ground.y - player.height;
        player.velocityY = 0;
        player.isGrounded = true;
    }
}