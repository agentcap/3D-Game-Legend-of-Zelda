#include "main.h"

#ifndef GIFT_H
#define GIFT_H


class Gift {
public:
    Gift() {}
    Gift(glm::vec3 position, float h, float s, float score, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
    float height;
    float size;
    float rotation;
    float score;
private:
    VAO *object;
};

#endif // GIFT_H
