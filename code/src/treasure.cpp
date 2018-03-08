#include "treasure.h"
#include "main.h"

#define PI 3.14159265

Treasure::Treasure(glm::vec3 position, float s) {
    this->position = position;
    this->size = s;
    this->rotation = 0;

    GLfloat vertex_buffer_data[] = {
        -s/2,-s/2,-s/2,
        -s/2,-s/2, s/2,
        -s/2, s/2, s/2,

        s/2, s/2,-s/2,
        -s/2,-s/2,-s/2,
        -s/2, s/2,-s/2,

        s/2,-s/2, s/2,
        -s/2,-s/2,-s/2,
        s/2,-s/2,-s/2,

        s/2, s/2,-s/2,
        s/2,-s/2,-s/2,
        -s/2,-s/2,-s/2,

        -s/2,-s/2,-s/2,
        -s/2, s/2, s/2,
        -s/2, s/2,-s/2,

        s/2,-s/2, s/2,
        -s/2,-s/2, s/2,
        -s/2,-s/2,-s/2,

        -s/2, s/2, s/2,
        -s/2,-s/2, s/2,
        s/2,-s/2, s/2,

        s/2, s/2, s/2,
        s/2,-s/2,-s/2,
        s/2, s/2,-s/2,

        s/2,-s/2,-s/2,
        s/2, s/2, s/2,
        s/2,-s/2, s/2,

        s/2, s/2, s/2,
        s/2, s/2,-s/2,
        -s/2, s/2,-s/2,

        s/2, s/2, s/2,
        -s/2, s/2,-s/2,
        -s/2, s/2, s/2,

        s/2, s/2, s/2,
        -s/2, s/2, s/2,
        s/2,-s/2, s/2
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_CYAN, GL_FILL);
}

void Treasure::draw(glm::mat4 VP) {
    Matrices.model      = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP       = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Treasure::tick() {
    this->rotation += 5;
}

bounding_box_t Treasure::bounding_box() {
    bounding_box_t boat_t;
    boat_t.position = this->position;
    boat_t.height = this->size;
    boat_t.width = this->size;
    boat_t.length = this->size;
    boat_t.rotation = this->rotation;

    return boat_t;
}
