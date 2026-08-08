#pragma once

#include <vector>
#include "PhysicsObject.h"

class PhysicsWorld
{
public:
    // Global physics settings
    float gravity = 0.3f;
    float friction = 0.8f;

    // All objects participating in the simulation
    std::vector<PhysicsObject> objects;

    // Update the physics simulation
    void update();

private:
    // Handle collisions between dynamic and static objects
    void resolveCollisions();
};