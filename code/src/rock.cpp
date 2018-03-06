#include "rock.h"
#include "main.h"

#define PI 3.14159265

Rock::Rock(glm::vec3 position, float l, float w,float h, float score, color_t color) {
    this->position  = position;
    this->length    = l;
    this->width     = w;
    this->height    = h;
    this->tag = 0;
    this->score = score;

    std::cout << "asdfasdfas       "<< this->position.x << "\n";

    GLfloat vertex_buffer_data[] = {
        -l/2, 0, -w/2,
        -l/2, 0, w/2,
        -l/2, h, w/2,

        -l/2, h, w/2,
        -l/2, h+0.4, -w/2,
        -l/2, 0, -w/2,

        -l/2, 0, -w/2,
        -l/2, h+0.4, -w/2,
        l/2, 0, -w/2,

        -l/2, h+0.4, -w/2,
        l/2, h+0.8, -w/2,
        l/2, 0, -w/2,

        l/2, 0, -w/2,
        l/2, 0, w/2,
        l/2, h+1, w/2,

        l/2, h+1, w/2,
        l/2, h+0.8, -w/2,
        l/2, 0, -w/2,

        -l/2, 0, w/2,
        -l/2, h, w/2,
        l/2, 0, w/2,

        -l/2, h, w/2,
        l/2, h+1, w/2,
        l/2, 0, w/2,

        -l/2, h+0.4, -w/2,
        -l/2, h, w/2,
        l/2, h+1, w/2,

        -l/2, h+0.4, -w/2,
        l/2, h+1, w/2,
        l/2, h+0.8, -w/2,

    };

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Rock::bounding_box() {
    bounding_box_t box;
    box.position = this->position + glm::vec3(0.0,(this->height+1.0)/2,0.0);
    box.length = this->length;
    box.width = this->width;
    box.height = this->height+1;

    return box;
}

//bool Rock::detect_intersection(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
////    if(this->tag <= 15) {
////        std::cout << "-----------------\n";
////        std::cout << " a.x " << a.x << " a.z "<<a.z << "\n";
////        std::cout << " b.x " << b.x << " b.z "<<b.z << "\n";
////        std::cout << " c.x " << c.x << " c.z "<<c.z << "\n";
////        std::cout << " d.x " << d.x << " d.z "<<d.z << "\n";
////    }

//    // Conisder verticall lines case
//    if (a.x == b.x && c.x == d.x) {
//        if (a.x != c.x) return false;
//        if(min(a.z,b.z) < min(c.z,d.z)) return min(a.z,b.z) <= min(c.z,d.z) && min(c.z,d.z) <= max(a.z,b.z);
//        else return min(c.z,d.z) <= min(a.z,b.z) && min(a.z,b.z) <= max(c.z,d.z);
//    }
//    else if (a.x == b.x) {
//        float m2 = (float)(c.z - d.z)/(float)(c.x - d.x);
//        float c2 = c.z - m2*c.x;
//        float z = m2*(a.x) + c2;
//        return (min(a.z,b.z) <= z && z <= max(a.z,b.z)) &&
//                (min(c.x,d.x) <= a.x && a.x <= max(c.x,d.x));
//    }
//    else if (c.x == d.x) {
//        float m1 = (float)(a.z - b.z)/(float)(a.x - b.x);
//        float c1 = a.z - m1*a.x;
//        float z = m1*(c.x) + c1;
//        return (min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x)) &&
//                (min(c.z,d.z) <= z && z <= max(c.z,d.z));
//    }

//    // Non vertical lines case
//    float m1 = (float)(a.z - b.z)/(float)(a.x - b.x);
//    float m2 = (float)(c.z - d.z)/(float)(c.x - d.x);

//    float c1 = a.z - m1*a.x;
//    float c2 = c.z - m2*c.x;

//    // Finding min and max
//    float min1, max1, min2,max2;
//    min1 = min(a.x,b.x);
//    max1 = max(a.x,b.x);
//    min2 = min(c.x,d.x);
//    max2 = max(c.x,d.x);

//    if (m1 == m2 && c1 == c2) {
//        return (min1 <= c.x && c.x <= max1) ||(min1 <= d.x && d.x <= max1);
//    }
//    else if (m1 == m2) return false;

//    float x = (c1-c2)/(m1 - m2);

//    return (min1 <= x && x <= max1 &&
//            min2 <= x && x <= max2);
//}

//bool Rock::detect_collision(bounding_box_t obj) {
//    // Check one is completly inside other

//    // Check for intersections
//    std::vector< std::pair<glm::vec3, glm::vec3> > rock_edges;
//    std::vector< std::pair<glm::vec3, glm::vec3> > obj_edges;

//    rock_edges.push_back(std::make_pair(this->position + glm::vec3(-this->length/2.0,0,-this->width/2.0),this->position + glm::vec3(this->length/2.0,0,-this->width/2.0)));
//    rock_edges.push_back(std::make_pair(this->position + glm::vec3(this->length/2.0,0,-this->width/2.0),this->position + glm::vec3(this->length/2.0,0,this->width/2.0)));
//    rock_edges.push_back(std::make_pair(this->position + glm::vec3(this->length/2.0,0,this->width/2.0),this->position + glm::vec3(-this->length/2.0,0,this->width/2.0)));
//    rock_edges.push_back(std::make_pair(this->position + glm::vec3(-this->length/2.0,0,this->width/2.0),this->position + glm::vec3(-this->length/2.0,0,-this->width/2.0)));

//    glm::vec3 obj_cord[] = {
//        obj.position + glm::vec3(obj.length/2*cos(obj.rotation*PI/180), 0, -obj.length/2*sin(obj.rotation*PI/180)) + glm::vec3(obj.width/2*sin(obj.rotation*PI/180), 0, obj.length/2*cos(obj.rotation*PI/180)),
//        obj.position + -glm::vec3(obj.length/2*cos(obj.rotation*PI/180), 0, -obj.length/2*sin(obj.rotation*PI/180)) + glm::vec3(obj.width/2*sin(obj.rotation*PI/180), 0, obj.length/2*cos(obj.rotation*PI/180)),
//        obj.position + glm::vec3(obj.length/2*cos(obj.rotation*PI/180), 0, -obj.length/2*sin(obj.rotation*PI/180)) - glm::vec3(obj.width/2*sin(obj.rotation*PI/180), 0, obj.length/2*cos(obj.rotation*PI/180)),
//        obj.position + -glm::vec3(obj.length/2*cos(obj.rotation*PI/180), 0, -obj.length/2*sin(obj.rotation*PI/180)) - glm::vec3(obj.width/2*sin(obj.rotation*PI/180), 0, obj.length/2*cos(obj.rotation*PI/180)),
//    };
//    obj_edges.push_back(std::make_pair(obj_cord[3], obj_cord[2]));
//    obj_edges.push_back(std::make_pair(obj_cord[2],obj_cord[0]));
//    obj_edges.push_back(std::make_pair(obj_cord[0], obj_cord[1]));
//    obj_edges.push_back(std::make_pair(obj_cord[1], obj_cord[3]));

//    bool is_collision = false;
//    for(int i=0; i<rock_edges.size();i++) {
//        for(int j=0;j<obj_edges.size();j++) {
//            if(this->detect_intersection(rock_edges[i].first, rock_edges[i].second,obj_edges[j].first, obj_edges[j].second)) is_collision = true;
////            if (is_collision) {
////            if(this->tag <=15) {
////                std::cout << "cos*o " << cos(obj.rotation*PI/180)*obj.length/2.0 <<"\n";
////                std::cout << "o " << obj.length/2.0 <<"\n";
////                std::cout << "cos " << cos(obj.rotation*PI/180) <<"\n";
////                std::cout << "a.x" << rock_edges[i].first.x << "a.z" << rock_edges[i].first.z << "\n";
////                std::cout << "b.x" << rock_edges[i].second.x << "a.z" << rock_edges[i].second.z << "\n";
////                std::cout << "c.x" << obj_edges[j].first.x << "c.z" << obj_edges[j].first.z << "\n";
////                std::cout << "d.x" << obj_edges[j].second.x << "d.z" << obj_edges[j].second.z << "\n";
////                std::cout << is_collision <<"\n-----------\n";
////                this->tag++;
////            }
////            }
//        }
//    }

//    return is_collision;
//}
