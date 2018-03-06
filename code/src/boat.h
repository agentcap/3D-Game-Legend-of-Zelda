#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(glm::vec3 position, float l, float w, float h);
    void draw(glm::mat4 VP);
    void tick();
    glm::vec3 position;
    float rotation;
    float speed_h;
    float speed_perp;
    float speed_v;
    float length;
    float width;
    float height;
    bounding_box_t bounding_box();
    bounding_box_t bounding_box_cannon();
private:
    VAO *object;
    VAO *sail;
    VAO *cloth;
};

#endif // BOAT_H
