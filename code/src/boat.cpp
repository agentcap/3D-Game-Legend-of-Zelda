#include "boat.h"
#include "main.h"
#define PI 3.14159265
#define FRICTION 0.05
#define GRAVITY 0.05

Boat::Boat(glm::vec3 position, float l, float w, float h) {
    this->position  = position;
    this->rotation  = rotation;
    this->speed_v   = 0;
    this->speed_h   = 0;
    this->speed_perp= 0;

    float front_ratio = 5;
    float sail_width = w/20;
    float sail_height = h*5;
    float width_ratio = 10;
    int no_triangles = 14;

//    this->length    = l + l/front_ratio;
    this->length    = l;
    this->width     = w + 1.0*w/width_ratio;
//    this->width     = w;
    this->height    = h*5;

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
            float(COLOR_WHITE.r)/255.0f, float(COLOR_WHITE.g)/255.0f, float(COLOR_WHITE.b)/255.0f,
            float(COLOR_WHITE.r)/255.0f, float(COLOR_WHITE.g)/255.0f, float(COLOR_WHITE.b)/255.0f,
    };

    this->sail = create3DObject(GL_TRIANGLES, 10*3, sail_vertex_data,COLOR_GREEN, GL_FILL);
    this->cloth = create3DObject(GL_TRIANGLES, 1*3, cloth_vertex_data,cloth_color_data, GL_FILL);

}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->sail);
    draw3DObject(this->cloth);
}

void Boat::tick() {
//    std::cout << "h " << this->speed_h << "per " << this->speed_perp <<"\n";
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

bounding_box_t Boat::bounding_box_cannon() {
    bounding_box_t boat_t;
    boat_t.position = this->position;
    boat_t.height = this->height;
    boat_t.width = this->width;
    boat_t.length = this->length;
    boat_t.rotation = this->rotation;

    return boat_t;
}

bounding_box_t Boat::bounding_box() {
    bounding_box_t boat_t;
    boat_t.position = this->position + glm::vec3(0.0, this->height/2, 0.0);
    float angle = 0;
    if(this->rotation > 0) {
        angle = -((int)(this->rotation/360))*360 + this->rotation;
    }
    else {
        angle = -((int)(this->rotation/360)-1)*360 + this->rotation;
    }
//    float angle = -((int)(this->rotation/360))*360 + this->rotation;
    if( (0 <= angle && angle<= 45) || (135 <= angle && angle <= 215) || (360-45 <= angle && angle <=360)) {
        boat_t.width = this->width;
        boat_t.length = this->length;
    }
    else {
        boat_t.length = this->width;
        boat_t.width = this->length;
    }
    boat_t.height = this->height/5;

    return boat_t;
}

