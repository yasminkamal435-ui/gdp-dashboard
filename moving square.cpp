#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

float squareX = 50.0f;
float squareY = 50.0f;
float squareSize = 60.0f;
float speed = 4.0f;
const int WIDTH = 800;
const int HEIGHT = 500;
bool keys[256];
float squareColor[3] = { 0.0f, 1.0f, 1.0f };

void keyDown(unsigned char key, int x, int y)
{
    keys[key] = true;
    if (key == ' ')
    {
        squareColor[0] = static_cast<float>(rand()) / RAND_MAX;
        squareColor[1] = static_cast<float>(rand()) / RAND_MAX;
        squareColor[2] = static_cast<float>(rand()) / RAND_MAX;
    }
}

void keyUp(unsigned char key, int x, int y) { keys[key] = false; }

void specialKeyDown(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: keys['U'] = true; break;
    case GLUT_KEY_DOWN: keys['D'] = true; break;
    case GLUT_KEY_LEFT: keys['L'] = true; break;
    case GLUT_KEY_RIGHT: keys['R'] = true; break;
    }
}

void specialKeyUp(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: keys['U'] = false; break;
    case GLUT_KEY_DOWN: keys['D'] = false; break;
    case GLUT_KEY_LEFT: keys['L'] = false; break;
    case GLUT_KEY_RIGHT: keys['R'] = false; break;
    }
}

void clampPosition()
{
    if (squareX < 0) squareX = 0;
    if (squareY < 0) squareY = 0;
    if (squareX + squareSize > WIDTH) squareX = WIDTH - squareSize;
    if (squareY + squareSize > HEIGHT) squareY = HEIGHT - squareSize;
}

void update()
{
    if (keys['U']) squareY -= speed;
    if (keys['D']) squareY += speed;
    if (keys['L']) squareX -= speed;
    if (keys['R']) squareX += speed;
    clampPosition();
}

void drawSquare()
{
    glBegin(GL_QUADS);
    glColor3f(squareColor[0], squareColor[1], squareColor[2]);
    glVertex2f(squareX, squareY);
    glVertex2f(squareX + squareSize, squareY);
    glVertex2f(squareX + squareSize, squareY + squareSize);
    glVertex2f(squareX, squareY + squareSize);
    glEnd();
}

void display()
{
    update();
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    glutSwapBuffers();
}

void timer(int = 0)
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Moving Square - OpenGL");
    GLenum err = glewInit();
    if (err != GLEW_OK) { std::cerr << "GLEW init failed\n"; return -1; }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.133f, 0.133f, 0.133f, 1.0f);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    timer();
    glutMainLoop();
    return 0;
}