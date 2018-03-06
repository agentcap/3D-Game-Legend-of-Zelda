#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(glm::vec3 position,glm::vec3 center, float s, float l,float r);
    void draw(glm::mat4 VP);
    void align_to(bounding_box_t boat, float v_angle);
    glm::vec3 position;
    glm::vec3 center;
    float h_angle;
    float v_angle;
    float boat_angle;
private:
    VAO *base_obj;
    VAO *top_obj;
};

#endif // CANNON_H
