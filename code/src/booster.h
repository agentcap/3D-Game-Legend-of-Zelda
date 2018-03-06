#include "main.h"

#ifndef BOOSTER_H
#define BOOSTER_H


class Booster {
public:
    Booster() {}
    Booster(glm::vec3 position, float h, float s, float power, color_t color);
    glm::vec3 position;
    float height;
    float size;
    float rotation;
    float power;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
    void tick();
private:
    VAO *base_obj;
    VAO *top_obj;
};

#endif // BOOSTER_H
