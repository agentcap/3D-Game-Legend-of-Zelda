#include "main.h"

#ifndef LAND_H
#define LAND_H


class Land
{
public:
    Land() {}
    Land(glm::vec3 position, float s, float h, color_t color);
    void draw(glm::mat4 VP);
    bool detect_collision(bounding_box_t a);
    bool detect_port(bounding_box_t a);
    bounding_box_t bounding_box();
    bool detect_out_ofbounds(bounding_box_t a);
    glm::vec3 position;
    float size;
    float height;
private:
    VAO *object;
    VAO *path;
    VAO *mount;
};

#endif // LAND_H
