#pragma once

enum class ColliderType
{
    Box,
    Circle
};

struct Collider
{
    ColliderType type = ColliderType::Box;

    float width = 0.0f;
    float height = 0.0f;

    float radius = 0.0f;
};