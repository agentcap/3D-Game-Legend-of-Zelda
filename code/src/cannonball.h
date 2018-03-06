#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class CannonBall {
public:
    CannonBall() {}
    CannonBall(glm::vec3 position, float s, float speed_x, float speed_y, float speed_z);
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
    glm::vec3 position;
    float size;
    float speed_x;
    float speed_y;
    float speed_z;
    float rotation;
private:
    VAO *object;

};

#endif // CANNONBALL_H
