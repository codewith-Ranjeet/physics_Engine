#pragma once

struct Collision
{
    bool hasCollision = false;

    // Direction to push the object out
    float normalX = 0.0f;
    float normalY = 0.0f;

    // Amount of overlap
    float penetration = 0.0f;
};