#include "cannon.h"
#include "main.h"

#define PI 3.14159265

Cannon::Cannon(glm::vec3 position,glm::vec3 center, float s, float l,float r) {
    this->position = position;
    this->center = center;
    this->h_angle = 0;
    this->v_angle = 45;

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

    this->base_obj = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_CYAN, GL_FILL);

    int idx = 0;
    float angle = 0;
    float theta = 0.1;
    GLfloat top_buffer_data[(int)(360.0/theta*6)];
    for(int i=0;i<360.0/theta;i++) {
        top_buffer_data[idx++] = r*cos(angle*PI/180);
        top_buffer_data[idx++] = 0;
        top_buffer_data[idx++] = r*sin(angle*PI/180);

        top_buffer_data[idx++] = r*cos(angle*PI/180);
        top_buffer_data[idx++] = l;
        top_buffer_data[idx++] = r*sin(angle*PI/180);

        angle += theta;
    }

    this->top_obj = create3DObject(GL_LINES, (int)(360.0/theta*2), top_buffer_data, COLOR_WHITE, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model      = glm::mat4(1.0f);
    Matrices.model     *= (glm::translate(this->center));
    Matrices.model     *= (glm::rotate((float) (this->h_angle * M_PI / 180.0f), glm::vec3(0, 1, 0)));
    Matrices.model     *= (glm::translate(this->position));
    glm::mat4 MVP       = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base_obj);

    Matrices.model      = glm::mat4(1.0f);
    Matrices.model     *= (glm::translate(this->center));
    Matrices.model     *= (glm::rotate((float) (this->h_angle * M_PI / 180.0f), glm::vec3(0, 1, 0)));
    Matrices.model     *= (glm::translate(this->position));
    Matrices.model     *= (glm::rotate((float) (this->v_angle * M_PI / 180.0f), glm::vec3(0, 0, -1)));
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->top_obj);
}

void Cannon::align_to(bounding_box_t boat, float v_angle) {
    this->center = boat.position;
    this->h_angle = boat.rotation;
    this->v_angle = v_angle;
}
