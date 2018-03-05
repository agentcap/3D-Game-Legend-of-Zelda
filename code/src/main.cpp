#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "rock.h"
#include "barrel.h"

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
vector<Rock> rocks;
vector<Barrel> barrels;

/* Variables in the game */

// Camera Specifications
int camera_view = 3; // 0 ->Follow cam view
float camera_distance = 4;
float camera_angle = 60;

/* Screen Customization */
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float screen_width = 20, screen_height = 10;

Timer t60(1.0 / 60);
Timer wind_timer(3.0);

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
    water.draw(VP);
    boat.draw(VP);

    for(int i=0;i<rocks.size();i++) {
        rocks[i].draw(VP);
    }

    for(int i=0;i<barrels.size();i++) {
        barrels[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump = glfwGetKey(window, GLFW_KEY_SPACE);
    int camera = glfwGetKey(window, GLFW_KEY_C);

    int temp = glfwGetKey(window, GLFW_KEY_W);

    if (up) boat.speed_h = 0.03;
    if (down) boat.speed_h = -0.03;
    if (left) boat.rotation += 3;
    if (right) boat.rotation -= 3;
    if (jump) boat.speed_v = 0.3;
    if (camera) camera_view = (camera_view + 1)%3;
    if (temp) boat.speed_perp = 0.3;
}

void tick_elements() {
    boat.tick();
}

void tick_collision() {

    if(water.detect_collision(boat.bounding_box())) {
        boat.position.y = 0;
    }

    for(int i=0;i<rocks.size();i++) {
        if(rocks[i].detect_collision(boat.bounding_box())) {
            cout << "Collision detected";
            rocks.erase(rocks.begin()+i);
            i--;
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water   = Water(glm::vec3(0.0,-0.01,0.0), 20.0, COLOR_BLUE);
    boat    = Boat(glm::vec3(0.0,0.0,0.0), 1.5, 0.75, 0.25);
    boat.rotation = 0;
    rocks.push_back(Rock(glm::vec3(2.50,0.0,2.0),0.5,0.5,0.25,COLOR_BROWN));
    barrels.push_back(Barrel(glm::vec3(5,0,5),1,0.3));

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
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

//            if(rand()%1 == 0) {
//                wind_active = 1;
//                wind_direction = 90;
//            }
//            if (wind_active) {
//                boat.speed_perp += 0.02*sin((wind_direction - boat.rotation)*PI/180);
//                boat.speed_h += 0.02*cos((wind_direction - boat.rotation)*PI/180);
//                boat.rotation += find_rotate_dir(wind_direction, boat.rotation);
//                if (wind_timer.processTick()) wind_active = 0;
//            }
            tick_elements();
            tick_collision();;
            tick_input(window);
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
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::infinitePerspective(45.0f,2.0f,0.1f);
}

void adjust_camera() {
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    // Follow-cam view
    if (camera_view == 0) {
        float y_cord = boat.position.y + camera_distance * cos(camera_angle*PI/180);
        float x_cord = boat.position.x - camera_distance * sin(camera_angle*PI/180) * cos(boat.rotation*PI/180);
        float z_cord = boat.position.z + camera_distance * sin(camera_angle*PI/180) * sin(boat.rotation*PI/180);

        eye     = glm::vec3(x_cord, y_cord, z_cord);
        target  = boat.position;
        up      = glm::vec3(0, 1, 0);
    }
    // Boat view
    else if (camera_view == 1) {
        float view_angle = 110;
        eye     = boat.position + glm::vec3(boat.length/10*cos(boat.rotation*PI/180), boat.height*3.5, -boat.length/10*sin(boat.rotation*PI/180));
        target  = eye + glm::vec3(sin(view_angle*PI/180)*cos(boat.rotation*PI/180), cos(view_angle*PI/180), -sin(view_angle*PI/180)*sin(boat.rotation*PI/180));
        up      = glm::vec3(0, 1, 0);
    }
    // Top View
    else if (camera_view == 2) {
        float distance = 10;
        eye     = boat.position + glm::vec3(0,distance,0);
        target  = boat.position;
        up      = glm::vec3(cos(boat.rotation*PI/180), 0, -sin(boat.rotation*PI/180));
    }
    //Tower View
    else if (camera_view == 3) {
        glm::vec3 tower_cord (-10,10,0);
        eye     = glm::vec3( 2, 10, 10);
        target  = boat.position;
        up      = glm::vec3(0, 1, 0);
    }
    //Helicopter-cam View
    else {
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
