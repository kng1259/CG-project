#include "Mesh.h"
#include <math.h>

#define PI 3.1415926
#define COLORNUM 14

#include <iostream>

float ColorArr[COLORNUM][3] =
    {
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, {0.9, 0.9, 0.9}, {1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}, {0.1, 0.1, 0.}, {1.0, 1.0, 1.0}};

void Mesh::CreateCube(float fSize)
{
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

void Mesh::CreateTetrahedron()
{
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

void Mesh::CreateCuboid(float fSizeX, float fSizeY, float fSizeZ)
{
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

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
    numVerts = nSegment * 2 + 2;
    pt = new Point3[numVerts];

    int i;
    int idx;
    float fAngle = 2 * PI / nSegment;
    float x, y, z;

    pt[0].set(0, fHeight / 2, 0);
    for (i = 0; i < nSegment; i++)
    {
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
    for (i = 0; i < nSegment; i++)
    {
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

    for (i = 0; i < nSegment; i++)
    {
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

    for (i = 0; i < nSegment; i++)
    {
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

void Mesh::CreateCylinderWithHole(int nSegment, float fHeight, float fORadius, float fIRadius)
{
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

    for (int i = 0; i < nSegment; i++)
    {
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
        face[idx + nSegment].vert[2].vertIndex = face[idx + nSegment].vert[1].vertIndex + nSegment + 1;
        face[idx + nSegment].vert[3].vertIndex = face[idx + nSegment].vert[0].vertIndex + nSegment + 1;

        // Face CC'D'D
        face[idx + 2 * nSegment].nVerts = 4;
        face[idx + 2 * nSegment].vert = new VertexID[face[idx + 2 * nSegment].nVerts];
        face[idx + 2 * nSegment].vert[0].vertIndex = i + 2 * nSegment + 2;
        if (i < nSegment - 1)
            face[idx + 2 * nSegment].vert[1].vertIndex = i + 2 * nSegment + 3;
        else
            face[idx + 2 * nSegment].vert[1].vertIndex = 2 * nSegment + 2;
        face[idx + 2 * nSegment].vert[2].vertIndex = face[idx + 2 * nSegment].vert[1].vertIndex + nSegment + 1;
        face[idx + 2 * nSegment].vert[3].vertIndex = face[idx + 2 * nSegment].vert[0].vertIndex + nSegment + 1;

        // Face DD'A'A
        face[idx + 3 * nSegment].nVerts = 4;
        face[idx + 3 * nSegment].vert = new VertexID[face[idx + 3 * nSegment].nVerts];
        face[idx + 3 * nSegment].vert[0].vertIndex = i + 3 * nSegment + 3;
        if (i < nSegment - 1)
            face[idx + 3 * nSegment].vert[1].vertIndex = i + 3 * nSegment + 4;
        else
            face[idx + 3 * nSegment].vert[1].vertIndex = 3 * nSegment + 3;
        face[idx + 3 * nSegment].vert[2].vertIndex = face[idx + 3 * nSegment].vert[1].vertIndex - 3 * nSegment - 3;
        face[idx + 3 * nSegment].vert[3].vertIndex = face[idx + 3 * nSegment].vert[0].vertIndex - 3 * nSegment - 3;

        idx++;
    }
}

void Mesh::CreateShape1(float fOx, float fOz, float fIx, float fIz, float fH1, float fH2, float fH3)
{
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

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
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

void Mesh::CreateShape2(float fOx, float fz, float fIx, float fH1, float fH2)
{
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

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
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

auto rotationalMatrix(float alpha)
{
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

auto rotatePointYAxis(float x, float y, float z, float alpha)
{
    auto matrix = rotationalMatrix(alpha);
    float vector[4]{x, y, z, 1};
    float *result = new float[4];
    // matrix multiplication
    for (int i = 0; i < 4; i++)
    {
        result[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

void Mesh::CreateWheel(int nSegment, int hands, float fHeight, float fOORadius, float fOIRadius, float fIORadius, float fIIRadius)
{
    // create 2 wheels first and use their meshes
    Mesh *innerWheel = new Mesh();
    Mesh *outerWheel = new Mesh();
    outerWheel->CreateCylinderWithHole(nSegment, fHeight, fOORadius, fOIRadius);
    innerWheel->CreateCylinderWithHole(nSegment, fHeight, fIORadius, fIIRadius);
    int numVertsWheel = 2 * outerWheel->numVerts; // == outerWheel.numVerts + innerWheel.numVerts
    numVerts = numVertsWheel + 8 * hands;         // 8 vertices per hand
    pt = new Point3[numVerts];
    for (int i = 0; i < numVertsWheel / 2; i++)
    {
        pt[i] = outerWheel->pt[i];
        pt[i + numVertsWheel / 2] = innerWheel->pt[i];
    }
    int numFacesWheel = 2 * outerWheel->numFaces;
    numFaces = numFacesWheel + 4 * hands; // plus 4 faces per hand
    face = new Face[numFaces];
    for (int i = 0; i < numFacesWheel / 2; i++)
    {
        face[i] = outerWheel->face[i];
        face[i + numFacesWheel / 2] = innerWheel->face[i];
        // adjust inner wheel faces' vertices
        for (int j = 0; j < face[i + numFacesWheel / 2].nVerts; j++)
        {
            face[i + numFacesWheel / 2].vert[j].vertIndex += numVertsWheel / 2;
        }
    }

    // create new verticess
    float alpha = 360 / (hands + 0);
    for (int i = 0; i < hands; i++)
    {
        printf("angle = %f\n", alpha * i);
        auto pt0 = rotatePointYAxis(fOIRadius, fHeight / 2, fIORadius / 4, alpha * i);
        auto pt1 = rotatePointYAxis(fOIRadius, fHeight / 2, -fIORadius / 4, alpha * i);
        auto pt2 = rotatePointYAxis(fOIRadius, -fHeight / 2, -fIORadius / 4, alpha * i);
        auto pt3 = rotatePointYAxis(fOIRadius, -fHeight / 2, fIORadius / 4, alpha * i);
        auto pt4 = rotatePointYAxis(fIORadius * 0.8, fHeight / 2, fIORadius / 4, alpha * i);
        auto pt5 = rotatePointYAxis(fIORadius * 0.8, fHeight / 2, -fIORadius / 4, alpha * i);
        auto pt6 = rotatePointYAxis(fIORadius * 0.8, -fHeight / 2, -fIORadius / 4, alpha * i);
        auto pt7 = rotatePointYAxis(fIORadius * 0.8, -fHeight / 2, fIORadius / 4, alpha * i);

        pt[numVertsWheel + 8 * i + 0].set(pt0[0], pt0[1], pt0[2]);
        pt[numVertsWheel + 8 * i + 1].set(pt1[0], pt1[1], pt1[2]);
        pt[numVertsWheel + 8 * i + 2].set(pt2[0], pt2[1], pt2[2]);
        pt[numVertsWheel + 8 * i + 3].set(pt3[0], pt3[1], pt3[2]);
        pt[numVertsWheel + 8 * i + 4].set(pt4[0], pt4[1], pt4[2]);
        pt[numVertsWheel + 8 * i + 5].set(pt5[0], pt5[1], pt5[2]);
        pt[numVertsWheel + 8 * i + 6].set(pt6[0], pt6[1], pt6[2]);
        pt[numVertsWheel + 8 * i + 7].set(pt7[0], pt7[1], pt7[2]);

        face[numFacesWheel + 4 * i].nVerts = 4;
        face[numFacesWheel + 4 * i].vert = new VertexID[face[numFacesWheel + 4 * i].nVerts];
        face[numFacesWheel + 4 * i].vert[0].vertIndex = numVertsWheel + 8 * i;
        face[numFacesWheel + 4 * i].vert[1].vertIndex = numVertsWheel + 8 * i + 1;
        face[numFacesWheel + 4 * i].vert[2].vertIndex = numVertsWheel + 8 * i + 5;
        face[numFacesWheel + 4 * i].vert[3].vertIndex = numVertsWheel + 8 * i + 4;

        face[numFacesWheel + 4 * i + 1].nVerts = 4;
        face[numFacesWheel + 4 * i + 1].vert = new VertexID[face[numFacesWheel + 4 * i + 1].nVerts];
        face[numFacesWheel + 4 * i + 1].vert[0].vertIndex = numVertsWheel + 8 * i + 2;
        face[numFacesWheel + 4 * i + 1].vert[1].vertIndex = numVertsWheel + 8 * i + 3;
        face[numFacesWheel + 4 * i + 1].vert[2].vertIndex = numVertsWheel + 8 * i + 7;
        face[numFacesWheel + 4 * i + 1].vert[3].vertIndex = numVertsWheel + 8 * i + 6;

        face[numFacesWheel + 4 * i + 2].nVerts = 4;
        face[numFacesWheel + 4 * i + 2].vert = new VertexID[face[numFacesWheel + 4 * i + 2].nVerts];
        face[numFacesWheel + 4 * i + 2].vert[0].vertIndex = numVertsWheel + 8 * i + 1;
        face[numFacesWheel + 4 * i + 2].vert[1].vertIndex = numVertsWheel + 8 * i + 2;
        face[numFacesWheel + 4 * i + 2].vert[2].vertIndex = numVertsWheel + 8 * i + 6;
        face[numFacesWheel + 4 * i + 2].vert[3].vertIndex = numVertsWheel + 8 * i + 5;

        face[numFacesWheel + 4 * i + 3].nVerts = 4;
        face[numFacesWheel + 4 * i + 3].vert = new VertexID[face[numFacesWheel + 4 * i + 3].nVerts];
        face[numFacesWheel + 4 * i + 3].vert[0].vertIndex = numVertsWheel + 8 * i + 0;
        face[numFacesWheel + 4 * i + 3].vert[1].vertIndex = numVertsWheel + 8 * i + 3;
        face[numFacesWheel + 4 * i + 3].vert[2].vertIndex = numVertsWheel + 8 * i + 7;
        face[numFacesWheel + 4 * i + 3].vert[3].vertIndex = numVertsWheel + 8 * i + 4;
    }
}

// A rectangle with a hole in the middle
void Mesh::CreateShape4(float fOx, float fOz, float fOy, float fIx, float fIz, float fIy)
{
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

    for (int i = 0; i < 4; i++)
    {
        face[i].nVerts = 4;
        face[i].vert = new VertexID[face[i].nVerts];
        face[i].vert[0].vertIndex = 4 * i;
        face[i].vert[1].vertIndex = 4 * i + 1;
        face[i].vert[2].vertIndex = 4 * i + 2;
        face[i].vert[3].vertIndex = 4 * i + 3;
    }
    for (int i = 0; i < 2; i++)
    {
        face[4 + i].nVerts = 4;
        face[4 + i].vert = new VertexID[face[4 + i].nVerts];
        face[4 + i].vert[0].vertIndex = 2 * i;
        face[4 + i].vert[1].vertIndex = 2 * i + 1;
        face[4 + i].vert[2].vertIndex = 2 * i + 5;
        face[4 + i].vert[3].vertIndex = 2 * i + 4;
    }
    for (int i = 0; i < 2; i++)
    {
        face[6 + i].nVerts = 4;
        face[6 + i].vert = new VertexID[face[6 + i].nVerts];
        face[6 + i].vert[0].vertIndex = 2 * i + 8;
        face[6 + i].vert[1].vertIndex = 2 * i + 9;
        face[6 + i].vert[2].vertIndex = 2 * i + 13;
        face[6 + i].vert[3].vertIndex = 2 * i + 12;
    }
    for (int i = 0; i < 4; i++)
    {
        face[8 + i].nVerts = 4;
        face[8 + i].vert = new VertexID[face[8 + i].nVerts];
        face[8 + i].vert[0].vertIndex = i;
        face[8 + i].vert[1].vertIndex = (i + 1) % 4;
        face[8 + i].vert[2].vertIndex = (i + 1) % 4 + 8;
        face[8 + i].vert[3].vertIndex = i + 8;
    }
    for (int i = 0; i < 4; i++)
    {
        face[12 + i].nVerts = 4;
        face[12 + i].vert = new VertexID[face[12 + i].nVerts];
        face[12 + i].vert[0].vertIndex = i + 4;
        face[12 + i].vert[1].vertIndex = (i + 1) % 4 + 4;
        face[12 + i].vert[2].vertIndex = (i + 1) % 4 + 12;
        face[12 + i].vert[3].vertIndex = i + 12;
    }
    for (int i = 0; i < 4; i++)
    {
        face[16 + i].nVerts = 4;
        face[16 + i].vert = new VertexID[face[16 + i].nVerts];
        face[16 + i].vert[0].vertIndex = i;
        face[16 + i].vert[1].vertIndex = i + 4;
        face[16 + i].vert[2].vertIndex = i + 12;
        face[16 + i].vert[3].vertIndex = i + 8;
    }
}

void Mesh::DrawWireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            int iv = face[f].vert[v].vertIndex;

            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}

void Mesh::SetColor(int colorIdx)
{
    for (int f = 0; f < numFaces; f++)
    {
        for (int v = 0; v < face[f].nVerts; v++)
        {
            face[f].vert[v].colorIndex = colorIdx;
        }
    }
}

void Mesh::DrawColor(int color)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (int f = 0; f < numFaces; f++)
    {
        glBegin(GL_POLYGON);
        for (int v = 0; v < face[f].nVerts; v++)
        {
            // SetColor(color);

            int iv = face[f].vert[v].vertIndex;
            int ic = face[f].vert[v].colorIndex;

            ic = f % COLORNUM;

            glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
        }
        glEnd();
    }
}
