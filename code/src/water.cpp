#include "water.h"
#include "main.h"

Water::Water(glm::vec3 position, float size, color_t color) {
    this->position  = position;

    GLfloat vertex_buffer_data[] = {
        size/2, 0.0f, size/2,
        size/2, 0.0f, -size/2,
        -size/2, 0.0f, -size/2,

        size/2, 0.0f, size/2,
        -size/2, 0.0f, size/2,
        -size/2, 0.0f, -size/2
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
