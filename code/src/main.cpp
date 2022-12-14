#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "rock.h"
#include "barrel.h"
#include "gift.h"
#include "booster.h"
#include "cannon.h"
#include "cannonball.h"
#include "monster.h"
#include "link.h"
#include "land.h"
#include "treasure.h"

#define PI 3.14159265

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

/* Objects in the game */
Water water;
Boat boat;
Link link;
Land land;
vector<Rock> rocks;
vector<Barrel> barrels;
vector<Gift> gifts;
vector<Booster> boosters;
Cannon cannon;
vector<CannonBall> cannon_balls;
vector<Monster> monsters;
Treasure treasure;

/* Game Status */
int PLAYER_SCORE = 0;
int PLAYER_HEALTH = 100;
int BOOST_COUNT = 100;
int KILL_CNT = 0;

bool BOAT_CTRL = true;

/* Variables in the game */

bool IS_ORTHO = false;
// Cannon orientation
float cannon_angle_v = 0;

// Camera Specifications
int camera_view = 0; // 0 ->Follow cam view
float camera_distance = 4;
float camera_angle = 70;

/* Screen Customization */
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float screen_width = 20, screen_height = 10;

Timer t60(1.0 / 60);
Timer wind_timer(3.0);
Timer respwan_timer(1.0);
Timer bgm(20);
Timer monster_timer(5.0);
int monster_sound;

bool start = true;
bool RESPWANING = false;
int last_drawn = 0;

/* Helicopter View */
float HELI_V = 70;
float HELI_H = 45;
float HELI_DIST = 5;
bool HELI_FLAG = false;

float P_HELI_V = 70;
float P_HELI_H = 45;

double MOUSE_X;
double MOUSE_Y;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    glUseProgram (programID);

    adjust_camera();

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    land.draw(VP);
    water.draw(VP);
    treasure.draw(VP);
    if( RESPWANING  == true) {
        if(last_drawn == 0) {
            boat.draw(VP);
            cannon.draw(VP);
            link.draw(VP);
        }
        last_drawn = (last_drawn + 1)%4;

        if(respwan_timer.processTick()) RESPWANING = false;
    }
    else{
        boat.draw(VP);
        cannon.draw(VP);
        link.draw(VP);
    }

    for(int i=0;i<rocks.size();i++) {
        rocks[i].draw(VP);
    }

    for(int i=0;i<barrels.size();i++) {
        barrels[i].draw(VP);
    }

    for(int i=0;i<gifts.size();i++) {
        gifts[i].draw(VP);
    }

    for(int i=0;i<boosters.size();i++) {
        boosters[i].draw(VP);
    }

    for(int i=0;i<cannon_balls.size();i++) {
        cannon_balls[i].draw(VP);
    }

    for(int i=0;i<monsters.size();i++) {
        monsters[i].draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int down = glfwGetKey(window, GLFW_KEY_S);
    int boost = glfwGetKey(window, GLFW_KEY_B);

    if(BOAT_CTRL) {
        if (boost) {
            if(BOOST_COUNT > 0) {
                BOOST_COUNT--;
                boat.speed_h += 0.1;
            }
        }
        else if (up) boat.speed_h = min(boat.speed_h+0.08,0.3);
        else if (down) boat.speed_h = max(boat.speed_h-0.08,-0.3);
        if (left) boat.rotation += 3;
        if (right) boat.rotation -= 3;
        angle_correlate(window);
        cannon.align_to(boat.bounding_box_cannon(), cannon_angle_v);
    }
    else {
        if (up) link.speed_h = min(link.speed_h+0.08,0.3);
        if (down) link.speed_h = max(link.speed_h-0.08,-0.3);
        if (left) link.rotation += 3;
        if (right) link.rotation -= 3;
    }
    if(BOAT_CTRL) link.align_to_boat(boat.bounding_box_cannon());
}

void jump_boat() {

    if(BOAT_CTRL && boat.position.y == 0.0) {
        boat.speed_v = 0.6;
        system(" canberra-gtk-play -f  ../music/resources/jump.wav --volume=\"1\"   &");
    }
    if(!BOAT_CTRL) {
        system(" canberra-gtk-play -f  ../music/resources/jump.wav --volume=\"1\"   &");
        link.speed_v = 0.6;
    }
}

void switch_camera() {
    camera_view = (camera_view + 1)%5;
}

void tick_elements() {
    if(BOAT_CTRL) boat.tick();
    else link.tick();

    for(int i=0;i<gifts.size();i++) {
        gifts[i].tick();
    }
    for(int i=0;i<boosters.size();i++) {
        boosters[i].tick();
    }
    for(int i=0;i<cannon_balls.size();i++) {
        cannon_balls[i].tick();
    }
    for(int i=0;i<monsters.size();i++) {
        monsters[i].tick(boat.bounding_box());
        if(monsters[i].type == 3 && monster_timer.processTick()) {
            system(" canberra-gtk-play -f  ../music/resources/boss.wav --volume=\"1\"   &");
        }
    }

    treasure.tick();
}

void tick_collision() {
    // 1. Water Boat collision
    // 2. Cannon Ball and Monster Collision
    // 3. Water and Cannon Ball Collision
    // 4. Boat and Cannons Collision
    // 5. Boat and Gifts
    // 6. Boat and Boosters
    // 7. Boat and Enemies
    // 8. Boat and Barrel

    if(!BOAT_CTRL) {
        if(land.detect_collision(link.bounding_box())) {
            link.position.y = land.position.y + land.height/2 + link.size/2;
        }
        if(land.detect_out_ofbounds(link.bounding_box())) {
            if(link.speed_h > 0) link.speed_h = -0.6;
            else link.speed_h = 0.6;
        }

        for(int i=0;i<gifts.size();i++) {
            if(detect_collision(link.bounding_box(), gifts[i].bounding_box())) {
                if(gifts[i].type == 0) PLAYER_SCORE += gifts[i].score;
                else PLAYER_HEALTH += gifts[i].score;
                gifts.erase(gifts.begin()+i);
                i--;
                system(" canberra-gtk-play -f  ../music/resources/gift.wav --volume=\"1\"   &");
            }
        }
        for(int i=0;i<monsters.size();i++) {
            if( detect_collision(link.bounding_box(), monsters[i].bounding_box())) {
                PLAYER_HEALTH -= 10;
                respwan();
            }
        }

    }

    if(water.detect_collision(boat.bounding_box())) {
        boat.position.y = 0;
    }
    if(water.detect_collision(link.bounding_box())) {
        link.position.y = 0;
    }
    for(int i=0;i<cannon_balls.size();i++) {
        if( water.detect_collision(cannon_balls[i].bounding_box()) ) {
            cannon_balls.erase(cannon_balls.begin()+i);
            i--;
        }
    }

    if(BOAT_CTRL) {
        for(int i=0;i<cannon_balls.size();i++) {
            for(int j=0;j<monsters.size();j++) {
                if( detect_collision(cannon_balls[i].bounding_box(),monsters[j].bounding_box())) {
                    cannon_balls.erase(cannon_balls.begin()+i);
                    monsters[j].health--;
                    if(monsters[j].health == 0) {
                        if(monsters[j].type == 3) {
                            boosters.push_back(Booster(monsters[j].position, 1,0.5, 100, COLOR_RED));
                        }
                        else {
                            if(rand()%2 == 0) gifts.push_back(Gift(monsters[j].position + glm::vec3(0,1,0),0.5,0.25, 10, 0, COLOR_GOLD));
                            else gifts.push_back(Gift(monsters[j].position + glm::vec3(0,1,0),0.5,0.25, 20, 1, COLOR_PURPLE));
                        }
                        PLAYER_SCORE += monsters[j].score;
                        monsters.erase(monsters.begin()+j);
                        system(" canberra-gtk-play -f  ../music/resources/enemy_collision.wav --volume=\"1\"   &");
                        i--;
                        j--;
                        KILL_CNT++;
                        if(KILL_CNT % 3 == 2) {
                            monsters.push_back(Monster(glm::vec3(-500+rand()%1000,0.0,-500 + rand()%1000),1.5,0.75,glm::vec3(0.1,0.1,0.1),3,50,COLOR_BLACK,4));
                        }
                    }
                }
            }
        }

        for(int i=0;i<rocks.size();i++) {
            if(detect_collision(boat.bounding_box(), rocks[i].bounding_box())) {
                PLAYER_HEALTH -= rocks[i].score;
                if(boat.speed_h > 0) boat.speed_h = -1;
                else boat.speed_h = 1;
                if(boat.position.y > 0) boat.speed_v = 0.5;
                system(" canberra-gtk-play -f  ../music/resources/rock_collision.wav --volume=\"1\"   &");
            }
        }

        for(int i=0;i<gifts.size();i++) {
            if(detect_collision(boat.bounding_box(), gifts[i].bounding_box())) {
                if(gifts[i].type == 0) PLAYER_SCORE += gifts[i].score;
                else PLAYER_HEALTH += gifts[i].score;
                gifts.erase(gifts.begin()+i);
                i--;
                system(" canberra-gtk-play -f  ../music/resources/gift.wav --volume=\"1\"   &");
            }
        }

        for(int i=0;i<boosters.size();i++) {
            if(detect_collision(boat.bounding_box(), boosters[i].bounding_box())) {
                BOOST_COUNT += boosters[i].power;
                boosters.erase(boosters.begin()+i);
                i--;
                system(" canberra-gtk-play -f  ../music/resources/gift.wav --volume=\"1\"   &");
            }
        }

        for(int i=0;i<monsters.size();i++) {
            if( detect_collision(boat.bounding_box(), monsters[i].bounding_box())) {
                PLAYER_HEALTH -= 10;
                respwan();
            }
        }

        for(int i=0;i<barrels.size();i++) {
            if( detect_collision(boat.bounding_box(), barrels[i].bounding_box())) {
                boat.speed_v = 10;
                boat.speed_h = 0.3;
            }
        }

        if(detect_collision(boat.bounding_box(), land.bounding_box())) {
            boat.speed_h = -1;
        }
    }
}

void generate_rocks(int no) {
    float score = 5;
    color_t color = COLOR_BROWN;
    for(int i=0;i<no;i++) {
        glm::vec3 pos(generate_rand_cord(), 0, generate_rand_cord());
        float length = 1 + (float)(rand()%200)/100;
        float width = 1 + (float)(rand()%200)/100;
        float height = 0.2 + (float)(rand()%100)/500;
        rocks.push_back(Rock(pos, length, width, height, score, color));
    }

}

void generate_gifts(int no) {
    for (int i=0;i<no;i++) {
        glm::vec3 pos = glm::vec3(generate_rand_cord(), 0, generate_rand_cord());
        barrels.push_back(Barrel(pos,1,0.3));
        gifts.push_back(Gift(pos + glm::vec3(0,1.2,0),0.5,0.25, 1, 20, COLOR_YELLOW));
    }

    gifts.push_back(Gift(land.position + glm::vec3(0, land.height*2, land.size/3),3,1, 100, 0, COLOR_YELLOW));

    for(int i=0;i<10;i++) {
        glm::vec3 pos = land.position + glm::vec3(-land.size/2 + rand()%int(land.size), land.height*2, -land.size/2 + rand()%int(land.size));
        gifts.push_back(Gift(pos,1,0.5, 15, rand()%2, COLOR_CYAN));
    }
}

void generate_monsters(int no) {
    for(int i=0;i<no;i++) {
        glm::vec3 pos = glm::vec3(generate_rand_cord(), 0, generate_rand_cord());
        int type = rand()%3;
        if(type == 0) monsters.push_back(Monster(pos,1.0,0.5,glm::vec3(0.15,0.15,0.15),type,5,COLOR_RED,1));
        if(type == 1) monsters.push_back(Monster(pos+ glm::vec3(0.0,3.0,0.0),1.0,0.5,glm::vec3(0.15,0.15,0.15),type,5,COLOR_RED,1));
        if(type == 2) monsters.push_back(Monster(pos,1.0,0.5,glm::vec3(0.15,0.15,0.15),type,10,COLOR_YELLOW,1));
    }

    monsters.push_back(Monster(land.position + glm::vec3(land.size/3,land.height/2,land.size/3),1.0,0.5,glm::vec3(0.15,0.15,0.15),2,5,COLOR_RED,1));
    monsters.push_back(Monster(land.position + glm::vec3(-land.size/3,land.height/2,land.size/3),1.0,0.5,glm::vec3(0.15,0.15,0.15),0,5,COLOR_YELLOW,1));
    monsters.push_back(Monster(land.position + glm::vec3(land.size/3,land.height/2,-land.size/3),1.0,0.5,glm::vec3(0.15,0.15,0.15),1,5,COLOR_BLUE,1));
    monsters.push_back(Monster(land.position + glm::vec3(-land.size/3,land.height/2,-land.size/3),1.0,0.5,glm::vec3(0.15,0.15,0.15),2,5,COLOR_ORANGE,1));
}

float generate_rand_cord() {
    return -50 + rand()%100;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water   = Water(glm::vec3(0.0,-0.01,0.0), 1000.0, COLOR_BLUE);
    boat    = Boat(glm::vec3(0.0,0.0,0.0), 1.5, 0.75, 0.25);
    link    = Link(boat.position, 0.3);
    land    = Land(glm::vec3(100,0.5,100), 50, 1, COLOR_MAROON);
    treasure = Treasure(land.position + glm::vec3(0,land.height/2,0),1);
    generate_rocks(30);
    generate_gifts(30);
    generate_monsters(15);
//    boosters.push_back(Booster(glm::vec3(10.0,0.0,10.0), 1,0.5, 100, COLOR_RED));
    cannon = Cannon(glm::vec3(boat.length/2,boat.height/5,0), boat.position,0.25,0.5,0.05);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    int wind_active = 0;
    float wind_direction = 0.0;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        if(bgm.processTick()||start) {
            start=false;
//            system(" canberra-gtk-play -f  ../music/resources/ocean.wav --volume=\"10\" &");
        }
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            if(BOAT_CTRL) {
                if(rand()%1000 == 0) {
                    wind_active = 1;
                    wind_direction = rand()%360;
                }
                if (wind_active) {
                    boat.speed_perp += 0.02*sin((wind_direction - boat.rotation)*PI/180);
                    boat.speed_h += 0.02*cos((wind_direction - boat.rotation)*PI/180);
                    boat.rotation += find_rotate_dir(wind_direction, boat.rotation);
                    if (wind_timer.processTick()) wind_active = 0;
                }
            }
            tick_elements();
            tick_collision();;
            tick_input(window);

            string Result;
            stringstream convert;

            convert << PLAYER_SCORE;
            Result = convert.str();

            const char *one = "Score ";
            const char *two = Result.c_str();
            const char *three = "   HEALTH ";
            string Result1;
            stringstream convert1;
            convert1 << PLAYER_HEALTH;
            Result1 = convert1.str();
            const char *four = Result1.c_str();

            string Result2;
            stringstream convert2;

            convert2 << BOOST_COUNT;
            Result2 = convert2.str();

            const char *five = "    BOOST ";
            const char *six = Result2.c_str();

            string total( string(one) + two + string(three) + four + string(five) + six);
            glfwSetWindowTitle(window, total.c_str());

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    if(IS_ORTHO) Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    else Matrices.projection = glm::infinitePerspective(45.0f,2.0f,0.1f);
}

void adjust_camera() {
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    glm::vec3 position;
    float rotation;
    if(BOAT_CTRL) {
        position = boat.position;
        rotation = boat.rotation;
    }
    else {
        position = link.position;
        rotation = link.rotation;
    }

    // Follow-cam view
    if (camera_view == 0) {
        float y_cord = position.y + camera_distance * cos(camera_angle*PI/180);
        float x_cord = position.x - camera_distance * sin(camera_angle*PI/180) * cos(rotation*PI/180);
        float z_cord = position.z + camera_distance * sin(camera_angle*PI/180) * sin(rotation*PI/180);

        eye     = glm::vec3(x_cord, y_cord, z_cord);
        target  = position;
        up      = glm::vec3(0, 1, 0);
    }
    // Boat view
    else if (camera_view == 1) {
        float view_angle = 110;
        eye     = position + glm::vec3(0.1*cos(rotation*PI/180), boat.height*0.5,-0.1*sin(rotation*PI/180) );
        target  = eye + glm::vec3(sin(view_angle*PI/180)*cos(rotation*PI/180), cos(view_angle*PI/180), -sin(view_angle*PI/180)*sin(rotation*PI/180));
        up      = glm::vec3(0, 1, 0);
    }
    // Top View
    else if (camera_view == 2) {
        float distance = 10;
        eye     = position + glm::vec3(0,distance,0);
        target  = position;
        up      = glm::vec3(cos(rotation*PI/180), 0, -sin(rotation*PI/180));
    }
    //Tower View
    else if (camera_view == 3) {
        eye     = glm::vec3(-10,10,0);
        target  = position;
        up      = glm::vec3(0, 1, 0);
    }
    //Helicopter-cam View
    else {
        double mouse_xpos, mouse_ypos;
        glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);

        double x=0.0;
        double y=0.0;
        if(HELI_FLAG) {
            x = mouse_xpos - MOUSE_X;
            y = mouse_ypos - MOUSE_Y;
        }
        float y_cord = position.y + HELI_DIST * cos((HELI_V+y/10.0)*PI/180);
        float x_cord = position.x - HELI_DIST * sin((HELI_V+y/10.0)*PI/180) * cos((HELI_H+x/10.0)*PI/180);
        float z_cord = position.z + HELI_DIST * sin((HELI_V+y/10.0)*PI/180) * sin((HELI_H+x/10.0)*PI/180);

        eye     = glm::vec3(x_cord, y_cord, z_cord);
        target  = position;
        up      = glm::vec3(0, 1, 0);
    }

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
}

float find_rotate_dir(float w_angle, float b_angle) {
    w_angle = -((int)(w_angle/360))*360 + w_angle;
    b_angle = -((int)(b_angle/360))*360 + b_angle;

    float dec_angle = 0.5;
    if(fabs(w_angle-b_angle) <= dec_angle) return w_angle-b_angle;

    if(w_angle < b_angle) {
        if(b_angle - w_angle < 180) return -dec_angle;
        else return dec_angle;
    }
    else {
        if(w_angle - b_angle < 180) return dec_angle;
        else return -dec_angle;
    }
}

void fire_cannon() {
    float speed = 0.3;

    glm::vec3 pos = boat.position + glm::vec3(cannon.position.x*cos(boat.rotation*PI/180), cannon.position.y, -cannon.position.x*sin(boat.rotation*PI/180));
    float speed_y = speed*cos(cannon.v_angle * PI/180);
    float speed_x = speed*sin(cannon.v_angle * PI/180)*cos(boat.rotation *PI/180);
    float speed_z = speed*sin(cannon.v_angle * PI/180)*sin(boat.rotation *PI/180);

    cannon_balls.push_back( CannonBall(pos, 0.1, speed_x, speed_y, speed_z) );
    system(" canberra-gtk-play -f  ../music/resources/cannon.wav --volume=\"1\"   &");
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
//            std::cout << "a.x " << a.position.x << "a.y " << a.position.y << "a.z " <<a.position.z <<"\n";
//            std::cout << "a.wid " << a.width << "a.height " << a.height << "a.length " <<a.length <<"\n";
//            std::cout << "b.x " << b.position.x << "b.y " << b.position.y << "b.z " <<b.position.z <<"\n";
//            std::cout << "b.wid " << b.width << "b.he " << b.height << "b.l " <<b.length <<"\n";

           return (abs(a.position.z - b.position.z)*2 < a.width + b.width) &&
                   (abs(a.position.y - b.position.y)*2 < a.height + b.height) &&
                   (abs(a.position.x - b.position.x)*2 < a.length + b.length);
}

void angle_correlate(GLFWwindow *window) {
    double mouse_xpos, mouse_ypos;
    glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
    float angle = 1 - 2*mouse_ypos/600.0;
    cannon_angle_v = (angle)*180.0/M_PI;
}

void store_cord() {
    HELI_FLAG = true;
    glfwGetCursorPos(window, &MOUSE_X, &MOUSE_Y);
}

void update_angle() {
    HELI_FLAG = false;
    double mouse_xpos, mouse_ypos;
    glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);

    double x = mouse_xpos - MOUSE_X;
    double y = mouse_ypos - MOUSE_Y;

    HELI_H += (x/10.0);
    HELI_V += (y/10.0);
}

void respwan() {
    if(BOAT_CTRL) {
        boat.speed_v  = 1;
        boat.speed_h = -1;
    }
    else {
        link.speed_v  = 1;
        link.speed_h = -1;
    }
    respwan_timer.processTick();
    RESPWANING = true;
}

void change_cntrl() {
    if(BOAT_CTRL && land.detect_port(link.bounding_box())) {
        link.position = land.position + glm::vec3(land.size/2-link.size/2,land.height + link.size/2,0);
        BOAT_CTRL = !BOAT_CTRL;
    }
    else if (land.detect_port(link.bounding_box())) {
        BOAT_CTRL = !BOAT_CTRL;
    }
}

void zoom_in() {
    HELI_DIST -= 0.1;
}

void zoom_out() {
    HELI_DIST += 0.1;
}

void change_pers() {
    IS_ORTHO = !IS_ORTHO;
    reset_screen();
}
