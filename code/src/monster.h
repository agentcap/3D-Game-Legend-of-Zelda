#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H


class Monster {
public:
    Monster() {}
    Monster(glm::vec3 position, float s, float h, glm::vec3 speed, int type, color_t color);
    void draw(glm::mat4 VP);
    void tick(bounding_box_t boat);
    bounding_box_t bounding_box();
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 speed;
    float size;
    float height;
    int type;
private:
    VAO *base_obj;
    VAO *top_obj;
};

#endif // MONSTER_H
