#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// Constants
const double pi = 3.14159265359;

// Camera parameters
double theta = pi / 4; // camera angle
double phi = pi / 4;   // camera angle
double R = 15;         // Camera radius

// Function to set camera position
void Camera_position(double R, double theta, double phi) {
    gluLookAt(R * sin(theta) * cos(phi), R * sin(theta) * sin(phi), R * cos(theta),
              0.0, 0.0, 0.0, // Look at the origin
              0.0, 0.0, 1.0  // Up vector
    );
}

// Function to draw a line segment
void Draw_segment(float V1[3], float V2[3]) {
    glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
    glEnd();
}

// Function to draw coordinate system
void Draw_coord_system() {
    float V1[3], V2[3];

    // X-axis
    glColor3f(1.0, 0.0, 0.0);
    V1[0] = -5.0; V1[1] = 0.0; V1[2] = 0.0;
    V2[0] = 5.0; V2[1] = 0.0; V2[2] = 0.0;
    Draw_segment(V1, V2);

    // Y-axis
    glColor3f(0.0, 1.0, 0.0);
    V1[0] = 0.0; V1[1] = -5.0; V1[2] = 0.0;
    V2[0] = 0.0; V2[1] = 5.0; V2[2] = 0.0;
    Draw_segment(V1, V2);

    // Z-axis
    glColor3f(0.0, 0.0, 1.0);
    V1[0] = 0.0; V1[1] = 0.0; V1[2] = -5.0;
    V2[0] = 0.0; V1[1] = 0.0; V2[2] = 5.0;
    Draw_segment(V1, V2);
}

// Function to draw a 3D pyramid
void DrawPyramid() {
    glBegin(GL_TRIANGLES);

    // Base vertices
    float V0[3] = {-2.0, -2.0, 0.0};
    float V1[3] = {2.0, -2.0, 0.0};
    float V2[3] = {2.0, 2.0, 0.0};
    float V3[3] = {-2.0, 2.0, 0.0};

    // Tip vertex
    float V4[3] = {0.0, 0.0, 5.0};

    // Front face
    glColor3f(1.0, 0.0, 0.0);
    glVertex3fv(V0);
    glVertex3fv(V1);
    glVertex3fv(V4);

    // Right face
    glColor3f(0.0, 1.0, 0.0);
    glVertex3fv(V1);
    glVertex3fv(V2);
    glVertex3fv(V4);

    // Back face
    glColor3f(0.0, 0.0, 1.0);
    glVertex3fv(V2);
    glVertex3fv(V3);
    glVertex3fv(V4);

    // Left face
    glColor3f(1.0, 1.0, 0.0);
    glVertex3fv(V3);
    glVertex3fv(V0);
    glVertex3fv(V4);

    glEnd();

    // Draw base
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3fv(V0);
    glVertex3fv(V1);
    glVertex3fv(V2);
    glVertex3fv(V3);
    glEnd();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Camera_position(R, theta, phi);
    Draw_coord_system();
    DrawPyramid();
}

// Main function
int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int running = 1;
    SDL_Event event;
    init();

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_LEFT) phi -= 0.1;
                    if (event.key.keysym.sym == SDLK_RIGHT) phi += 0.1;
                    if (event.key.keysym.sym == SDLK_UP) theta -= 0.1;
                    if (event.key.keysym.sym == SDLK_DOWN) theta += 0.1;
                    break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }

    SDL_Quit();
    return 0;
}
