#include "land.h"
#include "main.h"

Land::Land(glm::vec3 position, float s,float h, color_t color) {
    this->position = position;
    this->size = s;
    this->height = h;

    float w = s;
    float l = s;
    GLfloat vertex_buffer_data[] = {
        -w/2,-h/2,-l/2,
        -w/2,-h/2, l/2,
        -w/2, h/2, l/2,

        w/2, h/2,-l/2,
        -w/2,-h/2,-l/2,
        -w/2,h/2,-l/2,

        w/2,-h/2, l/2,
        -w/2,-h/2,-l/2,
        w/2,-h/2,-l/2,

        w/2, h/2,-l/2,
        w/2,-h/2,-l/2,
        -w/2,-h/2,-l/2,

        -w/2,-h/2,-l/2,
        -w/2, h/2, l/2,
        -w/2, h/2,-l/2,

        w/2,-h/2, l/2,
        -w/2,-h/2, l/2,
        -w/2,-h/2,-l/2,

        -w/2, h/2, l/2,
        -w/2,-h/2, l/2,
        w/2,-h/2, l/2,

        w/2, h/2, l/2,
        w/2,-h/2,-l/2,
        w/2, h/2,-l/2,

        w/2,-h/2,-l/2,
        w/2, h/2, l/2,
        w/2,-h/2, l/2,

        w/2, h/2, l/2,
        w/2, h/2,-l/2,
        -w/2, h/2,-l/2,

        w/2, h/2, l/2,
        -w/2, h/2,-l/2,
        -w/2, h/2, l/2,

        w/2, h/2, l/2,
        -w/2, h/2, l/2,
        w/2,-h/2, l/2
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    float temp = 0.0001;
    GLfloat side_buffer_data[] = {
        w/2,-h/2-temp,-l/8,
        w/2,-h/2-temp,+l/8,
        w/2+w/8,-h/2-temp,-l/8,

        w/2+w/8,-h/2-temp,-l/8,
        w/2+w/8,-h/2-temp,l/8,
        w/2,-h/2-temp,+l/8,

        w/2,h/2+temp,-l/8,
        w/2,h/2+temp,+l/8,
        w/2-w/8,h/2+temp,-l/8,

        w/2-w/8,h/2+temp,-l/8,
        w/2-w/8,h/2+temp,l/8,
        w/2,h/2+temp,+l/8,
    };
    this->path = create3DObject(GL_TRIANGLES, 4*3, side_buffer_data, COLOR_WHITE, GL_FILL);

    h = h*20;
    s = s/3;
    GLfloat mount_buffer_data[] = {
        s/2, 0, s/2,
        s/2, 0, -s/2,
        0, h/2, 0,

        s/2, 0, -s/2,
        -s/2, 0, -s/2,
        0, h/2, 0,

        -s/2, 0, -s/2,
        -s/2, 0, s/2,
        0, h/2, 0,

        -s/2, 0, s/2,
        s/2, 0, s/2,
        0, h/2, 0,


        s/2 + s/20, 0, s/2,
        s/2 + s/20, 0, -s/2,
        0 + s/20, h/2, 0,

        s/2 + s/20, 0, -s/2,
        -s/2 + s/20, 0, -s/2,
        0 + s/20, h/2, 0,

        -s/2 + s/20, 0, -s/2,
        -s/2 + s/20, 0, s/2,
        0 + s/20, h/2, 0,

        -s/2 + s/20, 0, s/2,
        s/2 + s/20, 0, s/2,
        0 + s/20, h/2, 0,

    };


    color_t temp1 = {0.0/255.0, 207.0/255.0, 31.0/255.0};

    GLfloat color_buffer_data[] = {
        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

        207.0/255.0, 22.0/255.0, 0.0,
        207.0/255.0, 22.0/255.0, 0.0,
        0.0/255.0, 207.0/255.0, 31.0/255.0,

    };

    this->mount = create3DObject(GL_TRIANGLES, 4*3, mount_buffer_data, color_buffer_data, GL_FILL);
}


void Land::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->path);
    draw3DObject(this->mount);
}

bounding_box_t Land::bounding_box() {
    bounding_box_t box;
    box.position = this->position;
    box.height = this->height;
    box.width = this->size;
    box.length = this->size;

    return box;
}

bool Land::detect_collision(bounding_box_t a) {
    return this->position.y + this->height/2 > a.position.y - a.height/2;
}

bool Land::detect_port(bounding_box_t a) {
    return (this->position.x + this->size/2 - this->size/8 <= a.position.x &&
            a.position.x <= this->position.x + this->size/2 + this->size/8) &&
            (this->position.z - this->size/8 <= a.position.z &&
             a.position.z <= this->position.z + this->size/8);
}

bool Land::detect_out_ofbounds(bounding_box_t a) {
    return !((this->position.x - this->size/2 <= a.position.x &&
            a.position.x <= this->position.x + this->size/2) &&
            (this->position.z - this->size/2 <= a.position.z &&
             a.position.z <= this->position.z + this->size/2));
}
