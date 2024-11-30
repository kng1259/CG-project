// Bai3.cpp : Defines the entry point for the console application.
//

#include "../include/Mesh.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>

#define PI 3.1415926
#define DEG2RAD(x) (x * PI) / 180.0f

using namespace std;

int screenWidth = 1000;
int screenHeight = 1000;

Mesh shape;
int nChoice = 1;

void drawAxis() {
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(4, 0, 0);

  glVertex3f(0, 0, 0);
  glVertex3f(0, 4, 0);

  glVertex3f(0, 0, -4);
  glVertex3f(0, 0, 4);
  glEnd();
}

void drawObject() {
  // translate whole object so its bottom is on Oxz plane
  glPushMatrix();
  glTranslatef(0, 2.5, 0);

  // Base
  // Box
  glPushMatrix();
  glTranslatef(0, -2.3, 0);
  shape.CreateCuboid(1.0, 0.2, 3);
  shape.DrawColor(1);
  glPopMatrix();

  // Shape 1
  glPushMatrix();
  shape.CreateShape1(0.5, 0.6, 0.3, 0.4, 3, 0.4, 0.2);
  glTranslatef(0, 0, -2.5);
  shape.DrawColor(2);
  glTranslatef(0, 0, 5);
  shape.DrawColor(2);
  glPopMatrix();

  // Shape 2
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glRotatef(90, 0, 1, 0);
  shape.CreateShape2(0.8, 0.3, 0.5, 4.0, 0.3);
  shape.DrawColor(3);
  glRotatef(180, 1, 0, 0);
  shape.DrawColor(3);
  glPopMatrix();

  // Cylinder
  glPushMatrix();
  glTranslatef(0.3, 0, 0);
  glRotatef(90, 0, 0, 1);
  shape.CreateCylinder(50, 0.6, 0.2);
  shape.DrawColor(7);
  glPopMatrix();

  // Wheel
  glPushMatrix();
  glTranslatef(0.4, 0, 0);
  glRotatef(90, 0, 0, 1);
  shape.CreateWheel(50, 5, 0.2, 1.5, 1, 0.5, 0.2);
  shape.DrawColor(5);
  glPopMatrix();

  // Small cylinder
  glPushMatrix();
  glTranslatef(0.7, 0, 0);
  glRotatef(90, 0, 0, 1);
  glTranslatef(-1.4, 0, 0);
  shape.CreateCylinder(50, 0.6, 0.1);
  shape.DrawColor(4);
  glPopMatrix();

  // Shape 4
  glPushMatrix();
  glTranslatef(0.8, 0, 0);
  shape.CreateShape4(0.2, 0.4, 3.4, 0.2, 0.2, 3.2);
  shape.DrawColor(0);
  glPopMatrix();

  // Support
  glPushMatrix();
  glTranslatef(0.55, 0, 2.5);
  shape.CreateCuboid(0.45, 0.15, 0.15);
  shape.DrawColor(1);
  glTranslatef(0, 0, -5);
  shape.DrawColor(1);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(0.8, 1.7, 0);
  shape.CreateCylinder(50, 3.0, 0.1);
  shape.DrawColor(4);
  glTranslatef(0, -3.4, 0);
  shape.DrawColor(4);
  glPopMatrix();

  glPopMatrix();
}

float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool b4View = false;

void myInit() {
  float fHalfSize = 3;

  glEnable(GL_DEPTH_TEST);

  camera_angle = 60.0;
  camera_height = 4.0;
  camera_dis = 11;
  camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
  camera_Y = camera_height;
  camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void mySetupCameraVolume(int nType) {
  if (nType == 4) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 1.0f,
                   1000.0f);
  } else if (nType == 1) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -1000, 1000);
  } else if (nType == 2) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -1000, 1000);
  } else if (nType == 3) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -1000, 1000);
  }
}

void DisplayOneView(int nType, int left, int right, int top, int bottom) {
  mySetupCameraVolume(nType);
  glViewport(left, top, right - left, bottom - top);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // code here
  if (nType == 1)
    gluLookAt(0, camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  else if (nType == 2)
    gluLookAt(0, 0.0, camera_dis, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  else if (nType == 3)
    gluLookAt(camera_dis, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  else
    gluLookAt(camera_X, camera_Y, camera_Z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  drawObject();
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (b4View == false) {
    DisplayOneView(4, 0, screenWidth, 0, screenHeight);
  } else {
    // code here
    DisplayOneView(1, 0, screenWidth / 2, 0, screenHeight / 2);
    DisplayOneView(2, 0, screenWidth / 2, screenHeight / 2, screenHeight);
    DisplayOneView(3, screenWidth / 2, screenWidth, screenHeight / 2,
                   screenHeight);
    DisplayOneView(4, screenWidth / 2, screenWidth, 0, screenHeight / 2);
    //
  }
  glFlush();
  glutSwapBuffers();
}

void changeCameraPos() {
  camera_X = sin(DEG2RAD(camera_angle)) * camera_dis;
  camera_Y = camera_height;
  camera_Z = cos(DEG2RAD(camera_angle)) * camera_dis;
  myDisplay();
}

void myKeyboard(unsigned char key, int x, int y) {
  switch (key) {
  // Code here
  case 'V':
  case 'v':
    b4View = !b4View;
    break;
  case '+':
    camera_dis += 0.1;
    changeCameraPos();
    break;
  case '-':
    camera_dis -= 0.1;
    changeCameraPos();
    break;
  }
  glutPostRedisplay();
}
void mySpecialKeyboard(int theKey, int mouseX, int mouseY) {
  // code here
  switch (theKey) {
  case GLUT_KEY_UP:
    camera_height += 0.1;
    changeCameraPos();
    break;
  case GLUT_KEY_DOWN:
    camera_height -= 0.1;
    changeCameraPos();
    break;
  case GLUT_KEY_LEFT:
    camera_angle += 1;
    changeCameraPos();
    break;
  case GLUT_KEY_RIGHT:
    camera_angle -= 1;
    changeCameraPos();
    break;
  }
}

int main(int argc, char *argv[]) {
  cout << "V, v: to switch between 1 and 4 views." << endl;
  cout << "+   : to increase camera distance." << endl;
  cout << "-   : to decrease camera distance." << endl;
  cout << "up arrow  : to increase camera height." << endl;
  cout << "down arrow: to decrease camera height." << endl;
  cout << "<-        : to rotate camera clockwise." << endl;
  cout << "->        : to rotate camera counterclockwise." << endl;

  glutInit(&argc, (char **)argv); // initialize the tool kit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH);               // set the display mode
  glutInitWindowSize(screenWidth, screenHeight); // set window size
  // glutInitWindowPosition(500, 500);                         // set window
  // position on screen
  glutCreateWindow("Project"); // open the screen window
  myInit();

  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(myDisplay);
  glutSpecialFunc(mySpecialKeyboard);

  glutMainLoop();
}
