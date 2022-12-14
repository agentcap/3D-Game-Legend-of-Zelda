#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(glm::vec3 position, float l, float w, float h, float score, color_t color);
    void draw(glm::mat4 VP);
    glm::vec3 position;
    bounding_box_t bounding_box();
//    bool detect_collision(bounding_box_t);
//    bool detect_intersection(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
    float height;
    float width;
    float length;
    int tag;
    float score;
private:
    VAO *object;

};

#endif // ROCK_H
