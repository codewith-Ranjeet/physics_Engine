#pragma once
#include <vector>
#include "physicsObject.h"

class physicsWorld
{
public:
    float gravity = 0.3f;   // gravity
    float friction = 0.85f; // friction to slowdown object
    
    std::vector<physicsObject> objects;

    void update();
};