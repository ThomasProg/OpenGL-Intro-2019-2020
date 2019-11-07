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