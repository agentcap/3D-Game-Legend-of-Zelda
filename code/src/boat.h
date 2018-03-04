#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat
{
public:
    Boat() {}
    Boat(glm::vec3 position, float l, float w, float h, float speed);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    float rotation;
    float speed;
private:
    VAO *object;
    VAO *sail;
    VAO *cloth;
};

#endif // BOAT_H
