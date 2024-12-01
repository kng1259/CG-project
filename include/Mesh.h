#if !defined(_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"

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

#endif
