#include "mesh.h"

#include "sphere.h"
#include "cube.h"

void Mesh::set(E_MeshType type)
{
    if (this->type != type)
    {
        vertices.clear();
        triangles.clear();
        switch (type)
        {
            case E_MeshType::E_SPHERE : 
                Construct::UVSphere(30, 30, *this);
                break;
            case E_MeshType::E_CUBE : 
                Construct::cube(*this);
                break;
            default:;
        }
        this->type = type;
    }
}