#include "main.h"

#ifndef TREASURE_H
#define TREASURE_H


class Treasure {
public:
    Treasure() {}
    Treasure(glm::vec3 position, float s);
    glm::vec3 position;
    float size;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TREASURE_H
