#include "barrel.h"
#include "main.h"

#define PI 3.14159265

Barrel::Barrel(glm::vec3 position, float l, float r) {
    this->position  = position;
    this->length    = l;
    this->radius    = r;

    float theta = 1, angle = 0;
    int no_triangles = (360.0/theta);

    GLfloat vertex_buffer_data[2*no_triangles*9];

    int idx = 0;
    for(int i=0;i<2;i++) {
        angle = 0;
        float pos;
        if(i == 0) pos = -l/2.0;
        else pos = l/2.0;
        for(int i=0;i<360.0/theta;i++) {
            vertex_buffer_data[idx++] = r*cos(angle*PI/180);
            vertex_buffer_data[idx++] = r*sin(angle*PI/180);
            vertex_buffer_data[idx++] = pos;

            vertex_buffer_data[idx++] = r*cos((angle+theta)*PI/180);
            vertex_buffer_data[idx++] = r*sin((angle+theta)*PI/180);
            vertex_buffer_data[idx++] = pos;


            vertex_buffer_data[idx++] = 0.0;
            vertex_buffer_data[idx++] = 0.0;
            vertex_buffer_data[idx++] = pos;

            angle += theta;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 2*no_triangles*3, vertex_buffer_data, COLOR_RED, GL_FILL);


    idx = 0;
    angle = 0;
    theta = 0.1;
    GLfloat top_buffer_data[(int)(180.0/theta*6)];
    for(int i=0;i<180.0/theta;i++) {
        top_buffer_data[idx++] = r*cos(angle*PI/180);
        top_buffer_data[idx++] = r*sin(angle*PI/180);
        top_buffer_data[idx++] = -l/2;

        top_buffer_data[idx++] = r*cos(angle*PI/180);
        top_buffer_data[idx++] = r*sin(angle*PI/180);
        top_buffer_data[idx++] = l/2;

        angle += theta;
    }

    this->top_object = create3DObject(GL_LINES, (int)(180.0/theta*2), top_buffer_data, COLOR_BLACK, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model      = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model     *= (translate);
    glm::mat4 MVP       = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->top_object);
}

bounding_box_t Barrel::bounding_box() {
    bounding_box_t box;
    box.position = this->position + glm::vec3(0.0, this->radius/2,0.0);
    box.height = this->radius;
    box.width = this->radius*2;
    box.length = this->length;

    return box;
}
