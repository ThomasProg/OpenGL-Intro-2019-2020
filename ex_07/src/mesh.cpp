#include "mesh.h"

#include "sphere.h"
#include "cube.h"
#include "maze.h"

void Mesh::setMesh(E_MeshType type)
{
    if (this->type != type)
    {
        vertices.clear();
        triangles.clear();
        switch (type)
        {
            case E_MeshType::E_SPHERE : 
                typeOfVerticies = E_VerticesType::E_TRIANGLES;
                Construct::UVSphere(30, 30, *this);
                break;
            case E_MeshType::E_CUBE : 
                typeOfVerticies = E_VerticesType::E_QUAD;
                Construct::cube(*this);
                break;
            case E_MeshType::E_MAZE : 
                typeOfVerticies = E_VerticesType::E_QUAD;
                Construct::maze(*this);
                break;
            default:;
        }
        this->type = type;
    }
}

void Mesh::draw_quadVersion()
{
    if (bShowEdges)
        glBegin(GL_LINE_LOOP);
    else 
        glBegin(GL_TRIANGLES);
        
    Vector3 p1 = {0.f, 0.f, 0.f};
    //since we know that triangles.size() is a multiple of 4 (it contains quads),
    //we do a loop unrolling for optimization
    for (unsigned int i = 0; i < triangles.size(); i+=4)
    {
        // b --- c
        // |   / |
        // | /   |
        // a --- d
    //Vector3Int dir[6] = {{0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}};
        // a - b - c
        // switch(i % 6)
        // {
        //     case 0 :
        //         glNormal3f(0.f, 1.f, 0.f);
        //         break;
        //     case 1 :
        //         glNormal3f(0.f, -1.f, 0.f);
        //         break;
        //     case 2 :
        //         glNormal3f(1.f, 0.f, 0.f);
        //         break;
        //     case 3 :
        //         glNormal3f(-1.f, 0.f, 0.f);
        //         break;
        //     case 4 :
        //         glNormal3f(0.f, 0.f, 1.f);
        //         break;
        //     case 5 :
        //         glNormal3f(0.f, 0.f, -1.f);
        //         break;
        // }
        glNormal3f(normals[i/4].x, normals[i/4].y, normals[i/4].z);

        p1 = vertices.at(triangles.at(i));
        //color(p1.x, p1.y, p1.z);
        glTexCoord2d(0, 1);
        glVertex3d(p1.x, p1.y, p1.z);
        
        p1 = vertices.at(triangles.at(i+1));
        //color(p1.x, p1.y, p1.z);
        glTexCoord2d(0, 0);
        glVertex3d(p1.x, p1.y, p1.z);

        p1 = vertices.at(triangles.at(i+2));
        glTexCoord2d(1, 0);
        glVertex3d(p1.x, p1.y, p1.z);

        // a - c - d
        p1 = vertices.at(triangles.at(i));
        glTexCoord2d(0, 1);
        glVertex3d(p1.x, p1.y, p1.z);

        p1 = vertices.at(triangles.at(i+2));
        glTexCoord2d(1, 0);
        glVertex3d(p1.x, p1.y, p1.z);

        p1 = vertices.at(triangles.at(i+3));
        glTexCoord2d(1, 1);
        glVertex3d(p1.x, p1.y, p1.z);
    }
    glEnd();
}