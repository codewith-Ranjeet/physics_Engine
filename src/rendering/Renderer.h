#pragma once

#include <SFML/Graphics.hpp>
#include "../physics/PhysicsObject.h"

class Renderer
{
private:
    sf::RenderWindow& window;

public:
    Renderer(sf::RenderWindow& window);

    void drawPlayer(const PhysicsObject& player);
    void drawGround(const PhysicsObject& ground);
};