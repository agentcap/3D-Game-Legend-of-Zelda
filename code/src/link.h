#include "main.h"

#ifndef LINK_H
#define LINK_H


class Link {
public:
    Link() {}
    Link(glm::vec3 position, float s);
    glm::vec3 position;
    float size;
    float rotation;
    float speed_h;
    float speed_perp;
    float speed_v;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
    void align_to_boat(bounding_box_t boat);
private:
    VAO *object;
};

#endif // LINK_H
