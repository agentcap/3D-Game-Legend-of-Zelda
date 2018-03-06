#include "booster.h"
#include "main.h"

Booster::Booster(glm::vec3 position, float h, float s, float power, color_t color) {
    this->position = position;
    this->height = h;
    this->size = s;
    this->rotation = 0;
    this->power = power;

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

    this->base_obj = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BROWN, GL_FILL);

    static const GLfloat top_buffer_data[] = {
        -s/2,s/2,0,
        -s/2,s/2+h,0,
        s/2,s/2 + h/2,0,
    };

    this->top_obj = create3DObject(GL_TRIANGLES, 1*4, top_buffer_data, COLOR_WHITE, GL_FILL);
}

void Booster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base_obj);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->top_obj);
}

void Booster::tick() {
    this->rotation += 1;
}

bounding_box_t Booster::bounding_box() {
    bounding_box_t box;
    box.position = this->position;
    box.height = this->height + this->size;
    box.width = this->size;
    box.length = this->size;

    return box;
}

