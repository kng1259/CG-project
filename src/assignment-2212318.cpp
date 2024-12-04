#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

class Point3 {
public:
  float x = 0, y = 0, z = 0;
  void set(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }
  void set(Point3 &p) {
    x = p.x;
    y = p.y;
    z = p.z;
  }
  Point3() { x = y = z = 0; }
  Point3(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }
};
class Color3 {
public:
  float r, g, b;
  void set(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
  }
  void set(Color3 &c) {
    r = c.r;
    g = c.g;
    b = c.b;
  }
  Color3() { r = g = b = 0; }
  Color3(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
  }
};
class Point2 {
public:
  Point2() { x = y = 0.0f; } // constructor 1
  Point2(float xx, float yy) {
    x = xx;
    y = yy;
  } // constructor 2
  void set(float xx, float yy) {
    x = xx;
    y = yy;
  }
  float getX() { return x; }
  float getY() { return y; }
  void draw() {
    glBegin(GL_POINTS);
    glVertex2f((GLfloat)x, (GLfloat)y);
    glEnd();
  }

private:
  float x, y;
};
class IntRect {
public:
  IntRect() {
    l = 0;
    r = 100;
    b = 0;
    t = 100;
  } // constructor
  IntRect(int left, int right, int bottom, int top) {
    l = left;
    r = right;
    b = bottom;
    t = top;
  }
  void set(int left, int right, int bottom, int top) {
    l = left;
    r = right;
    b = bottom;
    t = top;
  }
  void draw() {
    glRecti(l, b, r, t);
    glFlush();
  } // draw this rectangle using OpenGL
  int getWidth() { return (r - l); }
  int getHeight() { return (t - b); }

private:
  int l, r, b, t;
};

class RealRect {
public:
  RealRect() {
    l = 0;
    r = 100;
    b = 0;
    t = 100;
  } // constructor
  RealRect(float left, float right, float bottom, float top) {
    l = left;
    r = right;
    b = bottom;
    t = top;
  }
  void set(float left, float right, float bottom, float top) {
    l = left;
    r = right;
    b = bottom;
    t = top;
  }
  float getWidth() { return (r - l); }
  float getHeight() { return (t - b); }
  void draw() {
    glRectf(l, b, r, t);
    glFlush();
  }; // draw this rectangle using OpenGL
private:
  float l, r, b, t;
};

class Vector3 {
public:
  float x, y, z;
  void set(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }
  void set(Vector3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  void flip() {
    x = -x;
    y = -y;
    z = -z;
  }
  void normalize();
  Vector3() { x = y = z = 0; }
  Vector3(float dx, float dy, float dz) {
    x = dx;
    y = dy;
    z = dz;
  }
  Vector3(Vector3 &v) {
    x = v.x;
    y = v.y;
    z = v.z;
  }
  Vector3 cross(Vector3 b);
  float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b) {
  Vector3 c(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
  return c;
}
float Vector3::dot(Vector3 b) { return x * b.x + y * b.y + z * b.z; }
void Vector3::normalize() {
  float temp = sqrt(x * x + y * y + z * z);
  x = x / temp;
  y = y / temp;
  z = z / temp;
}

class VertexID {
public:
  int vertIndex;
  int colorIndex;
};

class Face {
public:
  int nVerts;
  VertexID *vert;

  Face() {
    nVerts = 0;
    vert = NULL;
  }
  ~Face() {
    if (vert != NULL) {
      delete[] vert;
      vert = NULL;
    }
    nVerts = 0;
  }
};

class Mesh {
public:
  int numVerts;
  Point3 *pt;

  int numFaces;
  Face *face;

  Point3 *faceNorm;
  Point3 *vertNorm;

public:
  Mesh() {
    numVerts = 0;
    pt = NULL;
    numFaces = 0;
    face = NULL;
  }
  ~Mesh() {
    if (pt != NULL) {
      delete[] pt;
    }
    if (face != NULL) {
      delete[] face;
    }
    numVerts = 0;
    numFaces = 0;
  }
  void DrawWireframe();
  void DrawColor(int);
  void SetColor(int);

  void CreateTetrahedron();
  void CreateCube(float fSize);
  void CreateCuboid(float, float, float);
  void CreateCylinder(int nSegment, float fHeight, float fRadius);
  void CreateCylinderWithHole(int nSegment, float fHeight, float fORadius,
                              float fIRadius);
  void CreateShape1(float fOx, float fOz, float fIx, float fIz, float fH1,
                    float fH2, float fH3);
  void CreateShape2(float, float, float, float, float);
  void CreateWheel(int nSegment, int hands, float fHeight, float fOORadius,
                   float fOIRadius, float fIORadius, float fIIRadius);
  void CreateShape4(float fOx, float fOz, float fOy, float fIx, float fIz,
                    float fIy);

  void CalculateFacesNorm(bool isInverted = false);
  void CalculateVertsNorm();
};

#define PI 3.1415926
#define COLORNUM 14

float ColorArr[COLORNUM][3] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5},
    {0.9, 0.9, 0.9}, {1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0},
    {0.1, 0.1, 0.},  {1.0, 1.0, 1.0}};

void Mesh::CreateCube(float fSize) {
  int i;

  numVerts = 8;
  pt = new Point3[numVerts];
  pt[0].set(-fSize, fSize, fSize);
  pt[1].set(fSize, fSize, fSize);
  pt[2].set(fSize, fSize, -fSize);
  pt[3].set(-fSize, fSize, -fSize);
  pt[4].set(-fSize, -fSize, fSize);
  pt[5].set(fSize, -fSize, fSize);
  pt[6].set(fSize, -fSize, -fSize);
  pt[7].set(-fSize, -fSize, -fSize);

  numFaces = 6;
  face = new Face[numFaces];

  // Left face
  face[0].nVerts = 4;
  face[0].vert = new VertexID[face[0].nVerts];
  face[0].vert[0].vertIndex = 1;
  face[0].vert[1].vertIndex = 5;
  face[0].vert[2].vertIndex = 6;
  face[0].vert[3].vertIndex = 2;
  for (i = 0; i < face[0].nVerts; i++)
    face[0].vert[i].colorIndex = 0;

  // Right face
  face[1].nVerts = 4;
  face[1].vert = new VertexID[face[1].nVerts];
  face[1].vert[0].vertIndex = 0;
  face[1].vert[1].vertIndex = 3;
  face[1].vert[2].vertIndex = 7;
  face[1].vert[3].vertIndex = 4;
  for (i = 0; i < face[1].nVerts; i++)
    face[1].vert[i].colorIndex = 1;

  // top face
  face[2].nVerts = 4;
  face[2].vert = new VertexID[face[2].nVerts];
  face[2].vert[0].vertIndex = 0;
  face[2].vert[1].vertIndex = 1;
  face[2].vert[2].vertIndex = 2;
  face[2].vert[3].vertIndex = 3;
  for (i = 0; i < face[2].nVerts; i++)
    face[2].vert[i].colorIndex = 2;

  // bottom face
  face[3].nVerts = 4;
  face[3].vert = new VertexID[face[3].nVerts];
  face[3].vert[0].vertIndex = 7;
  face[3].vert[1].vertIndex = 6;
  face[3].vert[2].vertIndex = 5;
  face[3].vert[3].vertIndex = 4;
  for (i = 0; i < face[3].nVerts; i++)
    face[3].vert[i].colorIndex = 3;

  // near face
  face[4].nVerts = 4;
  face[4].vert = new VertexID[face[4].nVerts];
  face[4].vert[0].vertIndex = 4;
  face[4].vert[1].vertIndex = 5;
  face[4].vert[2].vertIndex = 1;
  face[4].vert[3].vertIndex = 0;
  for (i = 0; i < face[4].nVerts; i++)
    face[4].vert[i].colorIndex = 4;

  // Far face
  face[5].nVerts = 4;
  face[5].vert = new VertexID[face[5].nVerts];
  face[5].vert[0].vertIndex = 3;
  face[5].vert[1].vertIndex = 2;
  face[5].vert[2].vertIndex = 6;
  face[5].vert[3].vertIndex = 7;
  for (i = 0; i < face[5].nVerts; i++)
    face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateTetrahedron() {
  int i;
  numVerts = 4;
  pt = new Point3[numVerts];
  pt[0].set(0, 0, 0);
  pt[1].set(1, 0, 0);
  pt[2].set(0, 1, 0);
  pt[3].set(0, 0, 1);

  numFaces = 4;
  face = new Face[numFaces];

  face[0].nVerts = 3;
  face[0].vert = new VertexID[face[0].nVerts];
  face[0].vert[0].vertIndex = 1;
  face[0].vert[1].vertIndex = 2;
  face[0].vert[2].vertIndex = 3;
  for (i = 0; i < face[0].nVerts; i++)
    face[0].vert[i].colorIndex = 0;

  face[1].nVerts = 3;
  face[1].vert = new VertexID[face[1].nVerts];
  face[1].vert[0].vertIndex = 0;
  face[1].vert[1].vertIndex = 2;
  face[1].vert[2].vertIndex = 1;
  for (i = 0; i < face[1].nVerts; i++)
    face[1].vert[i].colorIndex = 1;

  face[2].nVerts = 3;
  face[2].vert = new VertexID[face[2].nVerts];
  face[2].vert[0].vertIndex = 0;
  face[2].vert[1].vertIndex = 3;
  face[2].vert[2].vertIndex = 2;
  for (i = 0; i < face[2].nVerts; i++)
    face[2].vert[i].colorIndex = 2;

  face[3].nVerts = 3;
  face[3].vert = new VertexID[face[3].nVerts];
  face[3].vert[0].vertIndex = 1;
  face[3].vert[1].vertIndex = 3;
  face[3].vert[2].vertIndex = 0;
  for (i = 0; i < face[3].nVerts; i++)
    face[3].vert[i].colorIndex = 3;
}

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ) {
  int i;

  numVerts = 8;
  pt = new Point3[numVerts];
  pt[0].set(-fSizeX, fSizeY, fSizeZ);
  pt[1].set(fSizeX, fSizeY, fSizeZ);
  pt[2].set(fSizeX, fSizeY, -fSizeZ);
  pt[3].set(-fSizeX, fSizeY, -fSizeZ);
  pt[4].set(-fSizeX, -fSizeY, fSizeZ);
  pt[5].set(fSizeX, -fSizeY, fSizeZ);
  pt[6].set(fSizeX, -fSizeY, -fSizeZ);
  pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

  numFaces = 6;
  face = new Face[numFaces];

  // Left face
  face[0].nVerts = 4;
  face[0].vert = new VertexID[face[0].nVerts];
  face[0].vert[0].vertIndex = 1;
  face[0].vert[1].vertIndex = 5;
  face[0].vert[2].vertIndex = 6;
  face[0].vert[3].vertIndex = 2;
  for (i = 0; i < face[0].nVerts; i++)
    face[0].vert[i].colorIndex = 0;

  // Right face
  face[1].nVerts = 4;
  face[1].vert = new VertexID[face[1].nVerts];
  face[1].vert[0].vertIndex = 0;
  face[1].vert[1].vertIndex = 3;
  face[1].vert[2].vertIndex = 7;
  face[1].vert[3].vertIndex = 4;
  for (i = 0; i < face[1].nVerts; i++)
    face[1].vert[i].colorIndex = 1;

  // top face
  face[2].nVerts = 4;
  face[2].vert = new VertexID[face[2].nVerts];
  face[2].vert[0].vertIndex = 0;
  face[2].vert[1].vertIndex = 1;
  face[2].vert[2].vertIndex = 2;
  face[2].vert[3].vertIndex = 3;
  for (i = 0; i < face[2].nVerts; i++)
    face[2].vert[i].colorIndex = 2;

  // bottom face
  face[3].nVerts = 4;
  face[3].vert = new VertexID[face[3].nVerts];
  face[3].vert[0].vertIndex = 7;
  face[3].vert[1].vertIndex = 6;
  face[3].vert[2].vertIndex = 5;
  face[3].vert[3].vertIndex = 4;
  for (i = 0; i < face[3].nVerts; i++)
    face[3].vert[i].colorIndex = 3;

  // near face
  face[4].nVerts = 4;
  face[4].vert = new VertexID[face[4].nVerts];
  face[4].vert[0].vertIndex = 4;
  face[4].vert[1].vertIndex = 5;
  face[4].vert[2].vertIndex = 1;
  face[4].vert[3].vertIndex = 0;
  for (i = 0; i < face[4].nVerts; i++)
    face[4].vert[i].colorIndex = 4;

  // Far face
  face[5].nVerts = 4;
  face[5].vert = new VertexID[face[5].nVerts];
  face[5].vert[0].vertIndex = 3;
  face[5].vert[1].vertIndex = 2;
  face[5].vert[2].vertIndex = 6;
  face[5].vert[3].vertIndex = 7;
  for (i = 0; i < face[5].nVerts; i++)
    face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
  numVerts = nSegment * 2 + 2;
  pt = new Point3[numVerts];

  int i;
  int idx;
  float fAngle = 2 * PI / nSegment;
  float x, y, z;

  pt[0].set(0, fHeight / 2, 0);
  for (i = 0; i < nSegment; i++) {
    x = fRadius * cos(fAngle * i);
    z = fRadius * sin(fAngle * i);
    y = fHeight / 2;
    pt[i + 1].set(x, y, z);

    y = -fHeight / 2;
    pt[i + 1 + nSegment].set(x, y, z);
  }
  pt[numVerts - 1].set(0, -fHeight / 2, 0);

  numFaces = nSegment * 3;
  face = new Face[numFaces];

  idx = 0;
  for (i = 0; i < nSegment; i++) {
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = 0;
    if (i < nSegment - 1)
      face[idx].vert[1].vertIndex = i + 2;
    else
      face[idx].vert[1].vertIndex = 1;
    face[idx].vert[2].vertIndex = i + 1;
    idx++;
  }

  for (i = 0; i < nSegment; i++) {
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];

    face[idx].vert[0].vertIndex = i + 1;
    if (i < nSegment - 1)
      face[idx].vert[1].vertIndex = i + 2;
    else
      face[idx].vert[1].vertIndex = 1;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

    idx++;
  }

  for (i = 0; i < nSegment; i++) {
    face[idx].nVerts = 3;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = numVerts - 1;
    if (i < nSegment - 1)
      face[idx].vert[2].vertIndex = i + 2 + nSegment;
    else
      face[idx].vert[2].vertIndex = 1 + nSegment;
    face[idx].vert[1].vertIndex = i + 1 + nSegment;
    idx++;
  }
}

void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fORadius,
                                  float fIRadius) {
  numVerts = 4 * nSegment + 4;
  pt = new Point3[numVerts];
  numFaces = 4 * nSegment;
  face = new Face[numFaces];

  int idx = 0;
  float fAngle = 2 * PI / nSegment;
  float x, y, z;

  pt[nSegment].set(0, fHeight / 2, 0);
  pt[2 * nSegment + 1].set(0, -fHeight / 2, 0);
  pt[3 * nSegment + 2].set(0, -fHeight / 2, 0);
  pt[4 * nSegment + 3].set(0, fHeight / 2, 0);

  for (int i = 0; i < nSegment; i++) {
    // Vertex A
    x = fORadius * cos(fAngle * i);
    z = fORadius * sin(fAngle * i);
    y = fHeight / 2;
    pt[i].set(x, y, z);

    // Vertex B
    y = -fHeight / 2;
    pt[i + nSegment + 1].set(x, y, z);

    // Vertex C
    x = fIRadius * cos(fAngle * i);
    z = fIRadius * sin(fAngle * i);
    pt[i + 2 * nSegment + 2].set(x, y, z);

    // Vertex D
    y = fHeight / 2;
    pt[i + 3 * nSegment + 3].set(x, y, z);

    // Face AA'B'B
    face[idx].nVerts = 4;
    face[idx].vert = new VertexID[face[idx].nVerts];
    face[idx].vert[0].vertIndex = i;
    if (i < nSegment - 1)
      face[idx].vert[1].vertIndex = i + 1;
    else
      face[idx].vert[1].vertIndex = 0;
    face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment + 1;
    face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment + 1;

    // Face BB'C'C
    face[idx + nSegment].nVerts = 4;
    face[idx + nSegment].vert = new VertexID[face[idx + nSegment].nVerts];
    face[idx + nSegment].vert[0].vertIndex = i + nSegment + 1;
    if (i < nSegment - 1)
      face[idx + nSegment].vert[1].vertIndex = i + nSegment + 2;
    else
      face[idx + nSegment].vert[1].vertIndex = nSegment + 1;
    face[idx + nSegment].vert[2].vertIndex =
        face[idx + nSegment].vert[1].vertIndex + nSegment + 1;
    face[idx + nSegment].vert[3].vertIndex =
        face[idx + nSegment].vert[0].vertIndex + nSegment + 1;

    // Face CC'D'D
    face[idx + 2 * nSegment].nVerts = 4;
    face[idx + 2 * nSegment].vert =
        new VertexID[face[idx + 2 * nSegment].nVerts];
    face[idx + 2 * nSegment].vert[0].vertIndex = i + 2 * nSegment + 2;
    if (i < nSegment - 1)
      face[idx + 2 * nSegment].vert[1].vertIndex = i + 2 * nSegment + 3;
    else
      face[idx + 2 * nSegment].vert[1].vertIndex = 2 * nSegment + 2;
    face[idx + 2 * nSegment].vert[2].vertIndex =
        face[idx + 2 * nSegment].vert[1].vertIndex + nSegment + 1;
    face[idx + 2 * nSegment].vert[3].vertIndex =
        face[idx + 2 * nSegment].vert[0].vertIndex + nSegment + 1;

    // Face DD'A'A
    face[idx + 3 * nSegment].nVerts = 4;
    face[idx + 3 * nSegment].vert =
        new VertexID[face[idx + 3 * nSegment].nVerts];
    face[idx + 3 * nSegment].vert[0].vertIndex = i + 3 * nSegment + 3;
    if (i < nSegment - 1)
      face[idx + 3 * nSegment].vert[1].vertIndex = i + 3 * nSegment + 4;
    else
      face[idx + 3 * nSegment].vert[1].vertIndex = 3 * nSegment + 3;
    face[idx + 3 * nSegment].vert[2].vertIndex =
        face[idx + 3 * nSegment].vert[1].vertIndex - 3 * nSegment - 3;
    face[idx + 3 * nSegment].vert[3].vertIndex =
        face[idx + 3 * nSegment].vert[0].vertIndex - 3 * nSegment - 3;

    idx++;
  }
}

void Mesh::CreateShape1(float fOx, float fOz, float fIx, float fIz, float fH1,
                        float fH2, float fH3) {
  numVerts = 16;
  pt = new Point3[numVerts];
  numFaces = 14;
  face = new Face[numFaces];

  pt[0].set(fIx / 2, fH1 / 2, fIz / 2);
  pt[1].set(-fIx / 2, fH1 / 2, fIz / 2);
  pt[2].set(-fIx / 2, fH1 / 2, -fIz / 2);
  pt[3].set(fIx / 2, fH1 / 2, -fIz / 2);
  pt[4].set(fIx / 2, -fH1 / 2, fIz / 2);
  pt[5].set(-fIx / 2, -fH1 / 2, fIz / 2);
  pt[6].set(-fIx / 2, -fH1 / 2, -fIz / 2);
  pt[7].set(fIx / 2, -fH1 / 2, -fIz / 2);
  pt[8].set(fOx / 2, -fH1 / 2 - fH2, fOz / 2);
  pt[9].set(-fOx / 2, -fH1 / 2 - fH2, fOz / 2);
  pt[10].set(-fOx / 2, -fH1 / 2 - fH2, -fOz / 2);
  pt[11].set(fOx / 2, -fH1 / 2 - fH2, -fOz / 2);
  pt[12].set(fOx / 2, -fH1 / 2 - fH2 - fH3, fOz / 2);
  pt[13].set(-fOx / 2, -fH1 / 2 - fH2 - fH3, fOz / 2);
  pt[14].set(-fOx / 2, -fH1 / 2 - fH2 - fH3, -fOz / 2);
  pt[15].set(fOx / 2, -fH1 / 2 - fH2 - fH3, -fOz / 2);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      face[i * 4 + j].nVerts = 4;
      face[i * 4 + j].vert = new VertexID[face[i * 4 + j].nVerts];
      face[i * 4 + j].vert[0].vertIndex = j + i * 4;
      face[i * 4 + j].vert[1].vertIndex = (j + 1) % 4 + i * 4;
      face[i * 4 + j].vert[2].vertIndex = (j + 1) % 4 + i * 4 + 4;
      face[i * 4 + j].vert[3].vertIndex = j + i * 4 + 4;
    }
  }

  face[12].nVerts = 4;
  face[12].vert = new VertexID[face[12].nVerts];
  face[12].vert[0].vertIndex = 0;
  face[12].vert[1].vertIndex = 1;
  face[12].vert[2].vertIndex = 2;
  face[12].vert[3].vertIndex = 3;
  face[13].nVerts = 4;
  face[13].vert = new VertexID[face[13].nVerts];
  face[13].vert[0].vertIndex = 12;
  face[13].vert[1].vertIndex = 13;
  face[13].vert[2].vertIndex = 14;
  face[13].vert[3].vertIndex = 15;
}

void Mesh::CreateShape2(float fOx, float fz, float fIx, float fH1, float fH2) {
  numVerts = 12;
  pt = new Point3[numVerts];
  numFaces = 10;
  face = new Face[numFaces];

  pt[0].set(fIx / 2, fH1 / 2, fz / 2);
  pt[1].set(-fIx / 2, fH1 / 2, fz / 2);
  pt[2].set(-fIx / 2, fH1 / 2, -fz / 2);
  pt[3].set(fIx / 2, fH1 / 2, -fz / 2);
  pt[4].set(fIx / 2, -fH1 / 2, fz / 2);
  pt[5].set(-fIx / 2, -fH1 / 2, fz / 2);
  pt[6].set(-fIx / 2, -fH1 / 2, -fz / 2);
  pt[7].set(fIx / 2, -fH1 / 2, -fz / 2);
  pt[8].set(fOx / 2, -fH1 / 2 - fH2, fz / 2);
  pt[9].set(-fOx / 2, -fH1 / 2 - fH2, fz / 2);
  pt[10].set(-fOx / 2, -fH1 / 2 - fH2, -fz / 2);
  pt[11].set(fOx / 2, -fH1 / 2 - fH2, -fz / 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      face[i * 4 + j].nVerts = 4;
      face[i * 4 + j].vert = new VertexID[face[i * 4 + j].nVerts];
      face[i * 4 + j].vert[0].vertIndex = j + i * 4;
      face[i * 4 + j].vert[1].vertIndex = (j + 1) % 4 + i * 4;
      face[i * 4 + j].vert[2].vertIndex = (j + 1) % 4 + i * 4 + 4;
      face[i * 4 + j].vert[3].vertIndex = j + i * 4 + 4;
    }
  }

  face[8].nVerts = 4;
  face[8].vert = new VertexID[face[8].nVerts];
  face[8].vert[0].vertIndex = 0;
  face[8].vert[1].vertIndex = 1;
  face[8].vert[2].vertIndex = 2;
  face[8].vert[3].vertIndex = 3;
  face[9].nVerts = 4;
  face[9].vert = new VertexID[face[9].nVerts];
  face[9].vert[0].vertIndex = 8;
  face[9].vert[1].vertIndex = 9;
  face[9].vert[2].vertIndex = 10;
  face[9].vert[3].vertIndex = 11;
}

auto rotationalMatrix(float alpha) {
  auto matrix = new float[4][4]{0};
  float cosa = cos(alpha * PI / 180);
  float sina = sin(alpha * PI / 180);
  matrix[0][0] = cosa;
  matrix[2][2] = cosa;
  matrix[2][0] = sina;
  matrix[0][2] = -sina;
  matrix[1][1] = 1;
  matrix[3][3] = 1;
  return matrix;
}

auto rotatePointYAxis(float x, float y, float z, float alpha) {
  auto matrix = rotationalMatrix(alpha);
  float vector[4]{x, y, z, 1};
  float *result = new float[4];
  // matrix multiplication
  for (int i = 0; i < 4; i++) {
    result[i] = 0;
    for (int j = 0; j < 4; j++) {
      result[i] += matrix[i][j] * vector[j];
    }
  }
  return result;
}

void Mesh::CreateWheel(int nSegment, int hands, float fHeight, float fOORadius,
                       float fOIRadius, float fIORadius, float fIIRadius) {
  // create 2 wheels first and use their meshes
  Mesh *innerWheel = new Mesh();
  Mesh *outerWheel = new Mesh();
  outerWheel->CreateCylinderWithHole(nSegment, fHeight, fOORadius, fOIRadius);
  innerWheel->CreateCylinderWithHole(nSegment, fHeight, fIORadius, fIIRadius);
  int numVertsWheel =
      2 * outerWheel->numVerts; // == outerWheel.numVerts + innerWheel.numVerts
  numVerts = numVertsWheel + 8 * hands; // 8 vertices per hand
  pt = new Point3[numVerts];
  for (int i = 0; i < numVertsWheel / 2; i++) {
    pt[i] = outerWheel->pt[i];
    pt[i + numVertsWheel / 2] = innerWheel->pt[i];
  }
  int numFacesWheel = 2 * outerWheel->numFaces;
  numFaces = numFacesWheel + 4 * hands; // plus 4 faces per hand
  face = new Face[numFaces];
  for (int i = 0; i < numFacesWheel / 2; i++) {
    face[i] = outerWheel->face[i];
    face[i + numFacesWheel / 2] = innerWheel->face[i];
    // adjust inner wheel faces' vertices
    for (int j = 0; j < face[i + numFacesWheel / 2].nVerts; j++) {
      face[i + numFacesWheel / 2].vert[j].vertIndex += numVertsWheel / 2;
    }
  }

  // create new verticess
  float alpha = 360 / (hands + 0);
  for (int i = 0; i < hands; i++) {
    auto pt0 =
        rotatePointYAxis(fOIRadius, fHeight / 2, fIORadius / 4, alpha * i);
    auto pt1 =
        rotatePointYAxis(fOIRadius, fHeight / 2, -fIORadius / 4, alpha * i);
    auto pt2 =
        rotatePointYAxis(fOIRadius, -fHeight / 2, -fIORadius / 4, alpha * i);
    auto pt3 =
        rotatePointYAxis(fOIRadius, -fHeight / 2, fIORadius / 4, alpha * i);
    auto pt4 = rotatePointYAxis(fIORadius * 0.8, fHeight / 2, fIORadius / 4,
                                alpha * i);
    auto pt5 = rotatePointYAxis(fIORadius * 0.8, fHeight / 2, -fIORadius / 4,
                                alpha * i);
    auto pt6 = rotatePointYAxis(fIORadius * 0.8, -fHeight / 2, -fIORadius / 4,
                                alpha * i);
    auto pt7 = rotatePointYAxis(fIORadius * 0.8, -fHeight / 2, fIORadius / 4,
                                alpha * i);

    pt[numVertsWheel + 8 * i + 0].set(pt0[0], pt0[1], pt0[2]);
    pt[numVertsWheel + 8 * i + 1].set(pt1[0], pt1[1], pt1[2]);
    pt[numVertsWheel + 8 * i + 2].set(pt2[0], pt2[1], pt2[2]);
    pt[numVertsWheel + 8 * i + 3].set(pt3[0], pt3[1], pt3[2]);
    pt[numVertsWheel + 8 * i + 4].set(pt4[0], pt4[1], pt4[2]);
    pt[numVertsWheel + 8 * i + 5].set(pt5[0], pt5[1], pt5[2]);
    pt[numVertsWheel + 8 * i + 6].set(pt6[0], pt6[1], pt6[2]);
    pt[numVertsWheel + 8 * i + 7].set(pt7[0], pt7[1], pt7[2]);

    face[numFacesWheel + 4 * i].nVerts = 4;
    face[numFacesWheel + 4 * i].vert =
        new VertexID[face[numFacesWheel + 4 * i].nVerts];
    face[numFacesWheel + 4 * i].vert[0].vertIndex = numVertsWheel + 8 * i;
    face[numFacesWheel + 4 * i].vert[1].vertIndex = numVertsWheel + 8 * i + 1;
    face[numFacesWheel + 4 * i].vert[2].vertIndex = numVertsWheel + 8 * i + 5;
    face[numFacesWheel + 4 * i].vert[3].vertIndex = numVertsWheel + 8 * i + 4;

    face[numFacesWheel + 4 * i + 1].nVerts = 4;
    face[numFacesWheel + 4 * i + 1].vert =
        new VertexID[face[numFacesWheel + 4 * i + 1].nVerts];
    face[numFacesWheel + 4 * i + 1].vert[0].vertIndex =
        numVertsWheel + 8 * i + 2;
    face[numFacesWheel + 4 * i + 1].vert[1].vertIndex =
        numVertsWheel + 8 * i + 3;
    face[numFacesWheel + 4 * i + 1].vert[2].vertIndex =
        numVertsWheel + 8 * i + 7;
    face[numFacesWheel + 4 * i + 1].vert[3].vertIndex =
        numVertsWheel + 8 * i + 6;

    face[numFacesWheel + 4 * i + 2].nVerts = 4;
    face[numFacesWheel + 4 * i + 2].vert =
        new VertexID[face[numFacesWheel + 4 * i + 2].nVerts];
    face[numFacesWheel + 4 * i + 2].vert[0].vertIndex =
        numVertsWheel + 8 * i + 1;
    face[numFacesWheel + 4 * i + 2].vert[1].vertIndex =
        numVertsWheel + 8 * i + 2;
    face[numFacesWheel + 4 * i + 2].vert[2].vertIndex =
        numVertsWheel + 8 * i + 6;
    face[numFacesWheel + 4 * i + 2].vert[3].vertIndex =
        numVertsWheel + 8 * i + 5;

    face[numFacesWheel + 4 * i + 3].nVerts = 4;
    face[numFacesWheel + 4 * i + 3].vert =
        new VertexID[face[numFacesWheel + 4 * i + 3].nVerts];
    face[numFacesWheel + 4 * i + 3].vert[0].vertIndex =
        numVertsWheel + 8 * i + 0;
    face[numFacesWheel + 4 * i + 3].vert[1].vertIndex =
        numVertsWheel + 8 * i + 3;
    face[numFacesWheel + 4 * i + 3].vert[2].vertIndex =
        numVertsWheel + 8 * i + 7;
    face[numFacesWheel + 4 * i + 3].vert[3].vertIndex =
        numVertsWheel + 8 * i + 4;
  }
}

// A rectangle with a hole in the middle
void Mesh::CreateShape4(float fOx, float fOz, float fOy, float fIx, float fIz,
                        float fIy) {
  numVerts = 16;
  pt = new Point3[numVerts];
  numFaces = 20;
  face = new Face[numFaces];

  pt[0].set(fOx / 2, fOy / 2, fOz / 2);
  pt[1].set(-fOx / 2, fOy / 2, fOz / 2);
  pt[2].set(-fOx / 2, fOy / 2, -fOz / 2);
  pt[3].set(fOx / 2, fOy / 2, -fOz / 2);
  pt[4].set(fOx / 2, -fOy / 2, fOz / 2);
  pt[5].set(-fOx / 2, -fOy / 2, fOz / 2);
  pt[6].set(-fOx / 2, -fOy / 2, -fOz / 2);
  pt[7].set(fOx / 2, -fOy / 2, -fOz / 2);
  pt[8].set(fIx / 2, fIy / 2, fIz / 2);
  pt[9].set(-fIx / 2, fIy / 2, fIz / 2);
  pt[10].set(-fIx / 2, fIy / 2, -fIz / 2);
  pt[11].set(fIx / 2, fIy / 2, -fIz / 2);
  pt[12].set(fIx / 2, -fIy / 2, fIz / 2);
  pt[13].set(-fIx / 2, -fIy / 2, fIz / 2);
  pt[14].set(-fIx / 2, -fIy / 2, -fIz / 2);
  pt[15].set(fIx / 2, -fIy / 2, -fIz / 2);

  for (int i = 0; i < 4; i++) {
    face[i].nVerts = 4;
    face[i].vert = new VertexID[face[i].nVerts];
    face[i].vert[0].vertIndex = 4 * i;
    face[i].vert[1].vertIndex = 4 * i + 1;
    face[i].vert[2].vertIndex = 4 * i + 2;
    face[i].vert[3].vertIndex = 4 * i + 3;
  }
  for (int i = 0; i < 2; i++) {
    face[4 + i].nVerts = 4;
    face[4 + i].vert = new VertexID[face[4 + i].nVerts];
    face[4 + i].vert[0].vertIndex = 2 * i;
    face[4 + i].vert[1].vertIndex = 2 * i + 1;
    face[4 + i].vert[2].vertIndex = 2 * i + 5;
    face[4 + i].vert[3].vertIndex = 2 * i + 4;
  }
  for (int i = 0; i < 2; i++) {
    face[6 + i].nVerts = 4;
    face[6 + i].vert = new VertexID[face[6 + i].nVerts];
    face[6 + i].vert[0].vertIndex = 2 * i + 8;
    face[6 + i].vert[1].vertIndex = 2 * i + 9;
    face[6 + i].vert[2].vertIndex = 2 * i + 13;
    face[6 + i].vert[3].vertIndex = 2 * i + 12;
  }
  for (int i = 0; i < 4; i++) {
    face[8 + i].nVerts = 4;
    face[8 + i].vert = new VertexID[face[8 + i].nVerts];
    face[8 + i].vert[0].vertIndex = i;
    face[8 + i].vert[1].vertIndex = (i + 1) % 4;
    face[8 + i].vert[2].vertIndex = (i + 1) % 4 + 8;
    face[8 + i].vert[3].vertIndex = i + 8;
  }
  for (int i = 0; i < 4; i++) {
    face[12 + i].nVerts = 4;
    face[12 + i].vert = new VertexID[face[12 + i].nVerts];
    face[12 + i].vert[0].vertIndex = i + 4;
    face[12 + i].vert[1].vertIndex = (i + 1) % 4 + 4;
    face[12 + i].vert[2].vertIndex = (i + 1) % 4 + 12;
    face[12 + i].vert[3].vertIndex = i + 12;
  }
  for (int i = 0; i < 4; i++) {
    face[16 + i].nVerts = 4;
    face[16 + i].vert = new VertexID[face[16 + i].nVerts];
    face[16 + i].vert[0].vertIndex = i;
    face[16 + i].vert[1].vertIndex = i + 4;
    face[16 + i].vert[2].vertIndex = i + 12;
    face[16 + i].vert[3].vertIndex = i + 8;
  }
}

void Mesh::DrawWireframe() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  for (int f = 0; f < numFaces; f++) {
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    for (int v = 0; v < face[f].nVerts; v++) {
      int iv = face[f].vert[v].vertIndex;

      glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
    }
    glEnd();
  }
}

void Mesh::SetColor(int colorIdx) {
  for (int f = 0; f < numFaces; f++) {
    for (int v = 0; v < face[f].nVerts; v++) {
      face[f].vert[v].colorIndex = colorIdx;
    }
  }
}

void Mesh::DrawColor(int color) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (int f = 0; f < numFaces; f++) {
    glBegin(GL_POLYGON);
    for (int v = 0; v < face[f].nVerts; v++) {
      SetColor(color);

      int iv = face[f].vert[v].vertIndex;
      int ic = face[f].vert[v].colorIndex;

      // ic = f % COLORNUM;

      glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
      glNormal3f(vertNorm[iv].x, vertNorm[iv].y, vertNorm[iv].z);
      glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
    }
    glEnd();
  }
}

Point3 *calculateCrossProduct(Point3 a, Point3 b, Point3 c) {
  Point3 *result = new Point3();
  result->x = (b.y - a.y) * (c.z - a.z) - (b.z - a.z) * (c.y - a.y);
  result->y = (b.z - a.z) * (c.x - a.x) - (b.x - a.x) * (c.z - a.z);
  result->z = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return result;
}

Point3 *normalize(Point3 *a) {
  float length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
  Point3 *result = new Point3();
  result->x = a->x / length;
  result->y = a->y / length;
  result->z = a->z / length;
  return result;
}

void Mesh::CalculateFacesNorm(bool isInverted) {
  faceNorm = new Point3[numFaces];
  for (int i = 0; i < numFaces; i++) {
    int vert1 = face[i].vert[0].vertIndex;
    int vert2 = face[i].vert[1].vertIndex;
    int vert3 = face[i].vert[2].vertIndex;
    Point3 *cross = calculateCrossProduct(pt[vert1], pt[vert2], pt[vert3]);
    Point3 *norm = normalize(cross);
    if (isInverted) {
      faceNorm[i].x = -norm->x;
      faceNorm[i].y = -norm->y;
      faceNorm[i].z = -norm->z;
    } else {
      faceNorm[i].x = norm->x;
      faceNorm[i].y = norm->y;
      faceNorm[i].z = norm->z;
    }
    delete cross;
    delete norm;
  }
}

void Mesh::CalculateVertsNorm() {
  Point3 temp;
  vertNorm = new Point3[numVerts];
  for (int i = 0; i < numFaces; i++) {
    temp.set(faceNorm[i].x, faceNorm[i].y, faceNorm[i].z);
    for (int j = 0; j < face[i].nVerts; j++) {
      int vertIdx = face[i].vert[j].vertIndex;
      vertNorm[vertIdx].set(vertNorm[vertIdx].x + temp.x,
                            vertNorm[vertIdx].y + temp.y,
                            vertNorm[vertIdx].z + temp.z);
    }
  }
  Point3 *norm;
  for (int i = 0; i < numVerts; i++) {
    norm = normalize(&vertNorm[i]);
    vertNorm[i].set(norm->x, norm->y, norm->z);
    delete norm;
  }
}

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

void setMaterial(float dr, float dg, float db, float ar = 0.1, float ag = 0.1,
                 float ab = 0.1, float sr = 1, float sg = 1, float sb = 1) {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shiness = 100.8;

  ambient[0] = ar;
  ambient[1] = ag;
  ambient[2] = ab;
  ambient[3] = 1;
  diffuse[0] = dr;
  diffuse[1] = dg;
  diffuse[2] = db;
  diffuse[3] = 1;
  specular[0] = sr;
  specular[1] = sg;
  specular[2] = sb;
  specular[3] = 1;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

// wheel rotation parameters
float translatezf = 0.0;
float rotatef = 0.0;
bool bRotate = false;
bool bPlus = true;

// Wireframe toggle
float bWireFrame = false;

void drawObject() {
  // translate whole object so its bottom is on Oxz plane
  glPushMatrix();
  glTranslatef(0, 2.5, 0);

  // Base
  // Box
  setMaterial(0, 1, 0);
  glPushMatrix();
  glTranslatef(0, -2.3, 0);
  shape.CreateCuboid(1.0, 0.2, 3);
  shape.CalculateFacesNorm();
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(1);
  glPopMatrix();

  // Shape 1
  setMaterial(0, 0, 1);
  glPushMatrix();
  shape.CreateShape1(0.5, 0.6, 0.3, 0.4, 3, 0.4, 0.2);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  glTranslatef(0, 0, -2.5);
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(2);
  glTranslatef(0, 0, 5);
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(2);
  glPopMatrix();

  // Shape 2
  setMaterial(1, 1, 0);
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glRotatef(90, 0, 1, 0);
  glTranslatef(0, -1, 0);
  shape.CreateShape2(0.8, 0.3, 0.5, 2.0, 0.3);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(3);
  glRotatef(180, 1, 0, 0);
  glTranslatef(0, -2, 0);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(3);
  glPopMatrix();

  // Cylinder
  setMaterial(0.5, 0.5, 0.5);
  glPushMatrix();
  glTranslatef(0.3, 0, 0);
  glRotatef(90, 0, 0, 1);
  shape.CreateCylinder(50, 0.6, 0.2);
  shape.CalculateFacesNorm();
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(7);
  glPopMatrix();

  // Wheel
  setMaterial(0, 1, 1);
  glPushMatrix();
  glTranslatef(0.4, 0, 0);
  glRotatef(90, 0, 0, 1);
  glRotatef(rotatef, 0, 1, 0);
  shape.CreateWheel(50, 5, 0.2, 1.5, 1, 0.5, 0.2);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(5);

  // Small cylinder
  setMaterial(1, 0, 1);
  glTranslatef(-1.3, -0.3, 0);
  shape.CreateCylinder(20, 0.6, 0.1);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(4);
  glPopMatrix();

  // Shape 4
  setMaterial(1, 0, 0);
  glPushMatrix();
  glTranslatef(0.8, 0, translatezf);
  shape.CreateShape4(0.2, 0.4, 3.4, 0.2, 0.2, 3.2);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(0);
  glPopMatrix();

  // Support
  setMaterial(0, 1, 0);
  glPushMatrix();
  glTranslatef(0.55, 0, 2.5);
  shape.CreateCuboid(0.45, 0.15, 0.15);
  shape.CalculateFacesNorm();
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(1);
  glTranslatef(0, 0, -5);
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(1);
  glPopMatrix();

  setMaterial(1, 0, 1);
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(0.8, 2.2 + translatezf, 0);
  shape.CreateCylinder(20, 4.0, 0.1);
  shape.CalculateFacesNorm(true);
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
    shape.DrawColor(4);
  glTranslatef(0, -4.4, 0);
  shape.CalculateFacesNorm();
  shape.CalculateVertsNorm();
  if (bWireFrame)
    shape.DrawWireframe();
  else
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

const GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat lightAmbColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
const GLfloat lightPos[] = {5.0, 10.0, -5.0, 0.0};

void myInit() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);

  // set up the light
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

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

void calcTranslate() { translatezf = 1.3 * sin(DEG2RAD(rotatef)); }

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
  case '1':
    rotatef -= 1;
    calcTranslate();
    break;
  case '2':
    rotatef += 1;
    calcTranslate();
    break;
  case 'a':
  case 'A':
    bRotate = !bRotate;
    break;
  case 'b':
  case 'B':
    bPlus = !bPlus;
    break;
  case 'w':
  case 'W':
    bWireFrame = !bWireFrame;
    break;
  case 27:
    bRotate = false;
    exit(0);
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

void myIdle() {
  if (bRotate) {
    if (bPlus)
      rotatef += 1;
    else
      rotatef -= 1;
    calcTranslate();
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  cout << "1, 2: to rotate the wheel." << endl;
  cout << "A, a: to toggle rotating the wheel." << endl;
  cout << "B, b: to change auto wheel rotation direction." << endl;
  cout << "W, w: to toggle wireframe mode." << endl;
  cout << "V, v: to switch between 1 and 4 views." << endl;
  cout << "+   : to increase camera distance." << endl;
  cout << "-   : to decrease camera distance." << endl;
  cout << "up  : to increase camera height." << endl;
  cout << "down: to decrease camera height." << endl;
  cout << "<-  : to rotate camera clockwise." << endl;
  cout << "->  : to rotate camera counterclockwise." << endl;

  glutInit(&argc, (char **)argv); // initialize the tool kit
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH);               // set the display mode
  glutInitWindowSize(screenWidth, screenHeight); // set window size
  // glutInitWindowPosition(500, 500);                         // set window
  glutCreateWindow("Project"); // open the screen window
  myInit();

  glutKeyboardFunc(myKeyboard);
  glutDisplayFunc(myDisplay);
  glutSpecialFunc(mySpecialKeyboard);
  glutIdleFunc(myIdle);

  glutMainLoop();
}
