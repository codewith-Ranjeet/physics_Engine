#pragma once

struct physicsObject {
    float x = 0.0f; //x posisiton
    float y = 0.0f; // y position

    float velocityX = 0.0f;     // Current horizontal speed of object
    float velocityY = 0.0f;     // Current vertical speed of object
    float movementSpeed = 0.0f; // movement speed of object

    float height = 0.0f;        // height of object
    float width = 0.0f;         // width of object

    bool isStatic = false;      // check moving object
    bool isGrounded = false;    // check if on ground

    float prevY = 0.0f;         // store previous frame positionY of object
};