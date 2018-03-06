#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(glm::vec3 position, float l, float r);
    glm::vec3 position;
    float length;
    float radius;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *top_object;
};

#endif // BARREL_H
