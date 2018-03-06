#include "cannonball.h"
#include "main.h"

#define GRAVITY 0.01

CannonBall::CannonBall(glm::vec3 position, float s, float speed_x, float speed_y, float speed_z) {
    this->position = position;
    this->size  = s;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->speed_z = speed_z;
    this->rotation = 0;

    static const GLfloat vertex_buffer_data[] = {
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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void CannonBall::draw(glm::mat4 VP) {
    Matrices.model      = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    rotate             *= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP       = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void CannonBall::tick() {
    this->rotation += 1;
    this->position.x += this->speed_x;
    this->position.y += this->speed_y;
    this->position.z -= this->speed_z;

    this->speed_y -= GRAVITY;
}

bounding_box_t CannonBall::bounding_box() {
    bounding_box_t box;
    box.position = this->position;
    box.height = this->size;
    box.width = this->size;
    box.length = this->size;

    return box;
}
