#include "monster.h"
#include "main.h"

Monster::Monster(glm::vec3 position, float s, float h, glm::vec3 speed,int type, int score, color_t color,int health) {
    this->position = position;
    this->center = position;
    this->size = s;
    this->height = h;
    this->speed = speed;
    this->type = type;
    this->score = score;
    this->health = health;

    GLfloat vertex_buffer_data[] = {
        -s/2,-s/2+h,-s/2,
        -s/2,-s/2+h, s/2,
        -s/2, s/2+h, s/2,

        s/2, s/2+h,-s/2,
        -s/2,-s/2+h,-s/2,
        -s/2, s/2+h,-s/2,

        s/2,-s/2+h, s/2,
        -s/2,-s/2+h,-s/2,
        s/2,-s/2+h,-s/2,

        s/2, s/2+h,-s/2,
        s/2,-s/2+h,-s/2,
        -s/2,-s/2+h,-s/2,

        -s/2,-s/2+h,-s/2,
        -s/2, s/2+h, s/2,
        -s/2, s/2+h,-s/2,

        s/2,-s/2+h, s/2,
        -s/2,-s/2+h, s/2,
        -s/2,-s/2+h,-s/2,

        -s/2, s/2+h, s/2,
        -s/2,-s/2+h, s/2,
        s/2,-s/2+h, s/2,

        s/2, s/2+h, s/2,
        s/2,-s/2+h,-s/2,
        s/2, s/2+h,-s/2,

        s/2,-s/2+h,-s/2,
        s/2, s/2+h, s/2,
        s/2,-s/2+h, s/2,

        s/2, s/2+h, s/2,
        s/2, s/2+h,-s/2,
        -s/2, s/2+h,-s/2,

        s/2, s/2+h, s/2,
        -s/2, s/2+h,-s/2,
        -s/2, s/2+h, s/2,

        s/2, s/2+h, s/2,
        -s/2, s/2+h, s/2,
        s/2,-s/2+h, s/2
    };

    GLfloat cone_buffer_data[] = {
        -s/2,h+s/2,-s/2,
        -s/4,h+s/2+h,-s/4,
        0,h+s/2,0,

        s/2,h+s/2,s/2,
        s/4,h+s/2+h,s/4,
        0,h+s/2,0,
    };

    this->top_obj = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
    this->cone_obj = create3DObject(GL_TRIANGLES, 2*3, cone_buffer_data, COLOR_BLACK, GL_FILL);
}

void Monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->top_obj);
    draw3DObject(this->cone_obj);
}

void Monster::tick(bounding_box_t boat) {
    float force = 0.03;
    if (type == 0) {
        this->position.x += this->speed.x;
        if(this->position.x > this->center.x) this->speed.x -= force;
        else this->speed.x += force;
    }
    if (type == 1) {
        this->position.y += this->speed.y;
        if(this->position.y > this->center.y) this->speed.y -= force;
        else this->speed.y += force;
    }
    if (type == 2) {
        this->position.z += this->speed.z;
        if(this->position.z > this->center.z) this->speed.z -= force;
        else this->speed.z += force;
    }
    if (type == 3) {
        if(this->position.x < boat.position.x) this->position.x += 0.1;
        else this->position.x -= 0.1;

        if(this->position.z < boat.position.z) this->position.z += 0.1;
        else this->position.z -= 0.1;
    }
}

bounding_box_t Monster::bounding_box() {
    bounding_box_t box;
    box.position = this->position + glm::vec3(0,this->height,0);
    box.height = this->height;
    box.width = this->size;
    box.length = this->size;

    return box;
}
