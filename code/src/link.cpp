#include "link.h"
#include "main.h"

#define PI 3.14159265
#define FRICTION 0.05
#define GRAVITY 0.05

Link::Link(glm::vec3 position, float s) {
    this->position = position;
    this->size = s;
    this->rotation = 0;
    this->speed_v   = 0;
    this->speed_h   = 0;
    this->speed_perp= 0;

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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Link::draw(glm::mat4 VP) {
    Matrices.model      = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP       = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Link::tick() {
    this->position.x += (this->speed_h*cos(this->rotation*PI/180) - this->speed_perp*sin(this->rotation*PI/180));
    this->position.z -= (this->speed_h*sin(this->rotation*PI/180) + this->speed_perp*cos(this->rotation*PI/180));

    if (fabs(this->speed_h) <= FRICTION) this->speed_h = 0;
    else if (this->speed_h > 0) this->speed_h -= FRICTION;
    else this->speed_h += FRICTION;

    if (fabs(this->speed_perp) <= FRICTION) this->speed_perp = 0;
    else if (this->speed_perp > 0) this->speed_perp -= FRICTION;
    else this->speed_perp += FRICTION;

    this->position.y += this->speed_v;
    this->speed_v   -= GRAVITY;
}

void Link::align_to_boat(bounding_box_t boat) {
    this->position = boat.position;
    this->rotation = boat.rotation;
}

bounding_box_t Link::bounding_box() {
    bounding_box_t boat_t;
    boat_t.position = this->position;
    boat_t.height = this->size;
    boat_t.width = this->size;
    boat_t.length = this->size;
    boat_t.rotation = this->rotation;

    return boat_t;
}
