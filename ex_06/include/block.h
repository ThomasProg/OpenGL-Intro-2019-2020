#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "macros.h"
#include "mesh.h"
#include "cube.h"

enum class E_BlockTypes : char
{
    E_AIR,
    E_SIMPLE,
};

struct S_Block
{
    E_BlockTypes blockID = E_BlockTypes::E_AIR;

    S_Block() {}
    S_Block(E_BlockTypes block) : blockID(block) {}

    void addQuad(Mesh& mesh, Vector3 loc, Vector3 blockSize, const Vector3Int& direction)
    {
        //Construct::cube(mesh);
        if (direction.y == 1)
        {
            Vector3 p1 = loc;
            Vector3 p2 = p1 + Vector3(blockSize.x, 0, 0);
            Vector3 p3 = p1 + Vector3(0, 0, blockSize.z);
            Vector3 p4 = p1 + Vector3(blockSize.x, 0, blockSize.z);
            mesh.addQuad(p2, p1, p3, p4);
        }

        if (direction.x == -1)
        {
            Vector3 p1 = loc;
            Vector3 p2 = p1 + Vector3(blockSize.x, 0, 0);
            Vector3 p3 = p1 + Vector3(0, blockSize.z, 0);
            Vector3 p4 = p1 + Vector3(blockSize.x, blockSize.z, 0);
            mesh.addQuad(p2, p1, p3, p4);
        }
    }

    // static void getBlockID(Vector3 coordinates, Vector3 blockSize)
    // {
    //     return y + coordinates.y * nbElements.y < -1;
    // }
};

#endif