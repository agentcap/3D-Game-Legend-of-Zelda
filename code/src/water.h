#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(glm::vec3 position, float size, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bool detect_collision(bounding_box_t a);
private:
    VAO *object;
};

#endif // WATER_H
