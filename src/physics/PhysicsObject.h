#pragma once

#include "../collision/Collider.h"

struct PhysicsObject
{
    // Position
    float x = 0.0f;
    float y = 0.0f;

    // Velocity
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    // Physics properties
    float movementSpeed = 1.0f;

    bool isStatic = false;
    bool isGrounded = false;

    // Previous position
    float prevX = 0.0f;
    float prevY = 0.0f;

    // Collision shape
    Collider collider;
};