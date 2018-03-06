#include "gift.h"
#include "main.h"

Gift::Gift(glm::vec3 position, float h, float s,float score, color_t color) {
    this->position = position;
    this->height = h;
    this->size  = s;
    this->score = score;

    GLfloat vertex_buffer_data[] = {
        s/2, 0, s/2,
        s/2, 0, -s/2,
        -s/2, 0, s/2,

        -s/2, 0, s/2,
        -s/2, 0, -s/2,
        s/2, 0, -s/2,

        s/2, 0, s/2,
        s/2, 0, -s/2,
        0, h/2, 0,

        s/2, 0, s/2,
        s/2, 0, -s/2,
        0, -h/2, 0,

        s/2, 0, -s/2,
        -s/2, 0, -s/2,
        0, h/2, 0,

        s/2, 0, -s/2,
        -s/2, 0, -s/2,
        0, -h/2, 0,

        -s/2, 0, -s/2,
        -s/2, 0, s/2,
        0, h/2, 0,

        -s/2, 0, -s/2,
        -s/2, 0, s/2,
        0, -h/2, 0,

        -s/2, 0, s/2,
        s/2, 0, s/2,
        0, h/2, 0,

        -s/2, 0, s/2,
        s/2, 0, s/2,
        0, -h/2, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::tick() {
    this->rotation += 5;
}

bounding_box_t Gift::bounding_box() {
    bounding_box_t box;
    box.position = this->position;
    box.height = this->height;
    box.width = this->size;
    box.length = this->size;

    return box;
}
