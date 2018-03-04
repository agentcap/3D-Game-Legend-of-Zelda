#include "boat.h"
#include "main.h"

Boat::Boat(glm::vec3 position, float l, float w, float h, float speed) {
    this->position  = position;
    this->rotation  = rotation;
    this->speed     = speed;

    float front_ratio = 5;
    float sail_width = w/20;
    float sail_height = h*5;
    float width_ratio = 10;
    int no_triangles = 14;

    GLfloat vertex_buffer_data[] = {
        // Base
        -l/2, 0, -w/2,
        -l/2, 0, w/2,
        l/2, 0, w/2,

        -l/2, 0, -w/2,
        l/2, 0, -w/2,
        l/2, 0, w/2,

        l/2, 0, -w/2,
        l/2, 0, w/2,
        l/2 + l/front_ratio, 0, 0,

        //Heights
        -l/2, 0, -w/2,
        -l/2, 0, w/2,
        -l/2, h, w/2 + w/width_ratio,
        -l/2, h, w/2 + w/width_ratio,
        -l/2, 0, -w/2,
        -l/2, h, -w/2 - w/width_ratio,

        -l/2, 0, -w/2,
        l/2, 0, -w/2,
        -l/2, h, -w/2 - w/width_ratio,
        -l/2, h, -w/2 - w/width_ratio,
        l/2, h, -w/2  - w/width_ratio,
        l/2, 0, -w/2,

        -l/2, 0, w/2,
        l/2, 0, w/2,
        -l/2, h, w/2 + w/width_ratio,
        -l/2, h, w/2 + w/width_ratio,
        l/2, h, w/2 + w/width_ratio,
        l/2, 0, w/2,

        l/2, 0, -w/2,
        l/2 + l/front_ratio, 0, 0,
        l/2, h, -w/2 - w/width_ratio,
        l/2, h, -w/2 - w/width_ratio,
        l/2 + l/front_ratio, h, 0,
        l/2 + l/front_ratio, 0, 0,

        l/2, 0, w/2,
        l/2 + l/front_ratio, 0, 0,
        l/2, h, w/2 + w/width_ratio,
        l/2, h, w/2 + w/width_ratio,
        l/2 + l/front_ratio, h, 0,
        l/2 + l/front_ratio, 0, 0,

        // Top Lid
        l/2, h, -w/2 - w/width_ratio,
        l/2, h, w/2 + w/width_ratio,
        l/2 + l/front_ratio, h, 0,
    };

    color_t part_colors[] = {
        COLOR_BROWN,
        COLOR_BROWN,
        COLOR_BROWN,

        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,
        COLOR_RED,

        COLOR_BLACK,
    };

    GLfloat color_buffer_data[no_triangles*9];

    for(int i=0;i<no_triangles;i++) {
        color_buffer_data[i*9 + 0] = float(part_colors[i].r)/255.0f;
        color_buffer_data[i*9 + 1] = float(part_colors[i].g)/255.0f;
        color_buffer_data[i*9 + 2] = float(part_colors[i].b)/255.0f;

        color_buffer_data[i*9 + 3] = float(part_colors[i].r)/255.0f;
        color_buffer_data[i*9 + 4] = float(part_colors[i].g)/255.0f;
        color_buffer_data[i*9 + 5] = float(part_colors[i].b)/255.0f;

        color_buffer_data[i*9 + 6] = float(part_colors[i].r)/255.0f;
        color_buffer_data[i*9 + 7] = float(part_colors[i].g)/255.0f;
        color_buffer_data[i*9 + 8] = float(part_colors[i].b)/255.0f;
    };


    this->object = create3DObject(GL_TRIANGLES, no_triangles*3, vertex_buffer_data, color_buffer_data, GL_FILL);

    GLfloat sail_vertex_data[]    = {
        // Sail

        // Top Face
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        -sail_width/2 + l/10, sail_height, sail_width/2,
        sail_width/2 + l/10, sail_height, sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        sail_width/2 + l/10, sail_height, sail_width/2,
        sail_width/2 + l/10, sail_height, -sail_width/2,

        //Side Faces
        -sail_width/2 + l/10, 0, -sail_width/2,
        -sail_width/2 + l/10, 0, sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        -sail_width/2 + l/10, sail_height, sail_width/2,
        -sail_width/2 + l/10, 0, sail_width/2,

        sail_width/2 + l/10, 0, -sail_width/2,
        sail_width/2 + l/10, 0, sail_width/2,
        sail_width/2 + l/10, sail_height, -sail_width/2,
        sail_width/2 + l/10, sail_height, -sail_width/2,
        sail_width/2 + l/10, sail_height, sail_width/2,
        sail_width/2 + l/10, 0, sail_width/2,

        sail_width/2 + l/10, 0, -sail_width/2,
        -sail_width/2 + l/10, 0, -sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        sail_width/2 + l/10, sail_height, -sail_width/2,
        sail_width/2 + l/10, 0, -sail_width/2,

        sail_width/2 + l/10, 0, sail_width/2,
        -sail_width/2 + l/10, 0, sail_width/2,
        -sail_width/2 + l/10, sail_height, sail_width/2,
        -sail_width/2 + l/10, sail_height, sail_width/2,
        sail_width/2 + l/10, sail_height, sail_width/2,
        sail_width/2 + l/10, 0, sail_width/2,
    };

    GLfloat cloth_vertex_data[] = {
        //Sail Cloth
        -sail_width/2 + l/10, sail_height/5 , -sail_width/2,
        -sail_width/2 + l/10, sail_height, -sail_width/2,
        -sail_width/2- 2*l/3 + l/10, sail_height/5, -sail_width/2,
    };
    GLfloat cloth_color_data[] = {
            float(COLOR_WHITE.r)/255.0f, float(COLOR_WHITE.g)/255.0f, float(COLOR_WHITE.b)/255.0f,
            float(COLOR_BLACK.r)/255.0f, float(COLOR_BLACK.g)/255.0f, float(COLOR_BLACK.b)/255.0f,
            float(COLOR_WHITE.r)/255.0f, float(COLOR_WHITE.g)/255.0f, float(COLOR_WHITE.b)/255.0f,
    };

    this->sail = create3DObject(GL_TRIANGLES, 10*3, sail_vertex_data,COLOR_GREEN, GL_FILL);
    this->cloth = create3DObject(GL_TRIANGLES, 1*3, cloth_vertex_data,cloth_color_data, GL_FILL);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->sail);
    draw3DObject(this->cloth);
}
