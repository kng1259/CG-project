// Bai3.cpp : Defines the entry point for the console application.
//

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

using namespace std;

int screenWidth = 1600;
int screenHeight = 900;

Mesh shape;
int nChoice = 1;

void drawAxis()
{
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(4, 0, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 4, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 4);
    glEnd();
}
void myDisplay()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, screenWidth / 2, screenHeight);

    drawAxis();

    glColor3f(0, 0, 0);

    shape.DrawWireframe();

    glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight);

    drawAxis();
    shape.DrawColor(1);

    glFlush();
    glutSwapBuffers();
}

void myInit()
{
    float fHalfSize = 4;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char *argv[])
{
    cout << "1. Tetrahedron" << endl;
    cout << "2. Cube" << endl;
    cout << "3. Cylinder" << endl;
    cout << "4. Cuboid" << endl;
    cout << "5. Hollow Cylinder" << endl;
    cout << "6. Shape 1" << endl;
    cout << "7. Shape 2" << endl;
    cout << "8. Shape 3" << endl;
    cout << "9. Shape 4" << endl;
    cout << "Input the choice: " << endl;
    cin >> nChoice;

    glutInit(&argc, (char **)argv);                           // initialize the tool kit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
    glutInitWindowSize(screenWidth, screenHeight);            // set window size
    glutInitWindowPosition(500, 500);                         // set window position on screen
    glutCreateWindow("Lab 2");                                // open the screen window

    switch (nChoice)
    {
    case 1:
        shape.CreateTetrahedron();
        break;
    case 2:
        shape.CreateCube(1);
        break;
    case 3:
        shape.CreateCylinder(4, 2, 1);
        break;
    case 4:
        shape.CreateCuboid(1, 2, 1.5);
        break;
    case 5:
        shape.CreateCylinderWithHole(20, 3, 1.5, 1);
        break;
    case 6:
        shape.CreateShape1(2, 2, 1, 1, 4, 1, 0.2);
        break;
    case 7:
        shape.CreateShape2(2, 1, 1, 4, 1);
        break;
    case 8:
        shape.CreateWheel(100, 5, 1, 3, 2, 0.7, 0.2);
        break;
    case 9:
        shape.CreateShape4(2, 2, 4, 1, 1, 3);
        break;
    }

    myInit();
    glutDisplayFunc(myDisplay);

    glutMainLoop();
    return 0;
}

void projDisplay()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.5, 4, 2, 0, 0, 0, 0, 1, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Base
    // Box
    // Shape1
    shape.CreateShape1(1, 1.3, 0.5, 0.8, 6, 0.8, 0.4);
    glTranslatef(10, 0.5, 0);
    shape.DrawWireframe();
    glFlush();
    glutSwapBuffers();
}

// int main(int argc, char *argv[])
// {
//     glutInit(&argc, (char **)argv);                           // initialize the tool kit
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set the display mode
//     glutInitWindowSize(screenWidth, screenHeight);            // set window size
//     glutInitWindowPosition(500, 500);                         // set window position on screen
//     glutCreateWindow("Project");                              // open the screen window
//     myInit();
//     glutDisplayFunc(projDisplay);
//     glutMainLoop();
// }