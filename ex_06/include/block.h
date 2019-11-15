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
        if (direction.y == -1)
        {
            Vector3 p1 = loc;
            Vector3 p2 = p1 + Vector3(blockSize.x, 0, 0);
            Vector3 p3 = p1 + Vector3(0, 0, blockSize.z);
            Vector3 p4 = p1 + Vector3(blockSize.x, 0, blockSize.z);
            mesh.addQuad(p4, p3, p1, p2);
        }

        if (direction.y == 1)
        {
            Vector3 p1 = loc + Vector3(0, blockSize.y, 0);
            Vector3 p2 = loc + Vector3(blockSize.x, blockSize.y, 0);
            Vector3 p3 = loc + Vector3(0, blockSize.y, blockSize.z);
            Vector3 p4 = loc + Vector3(blockSize.x, blockSize.y, blockSize.z);
            mesh.addQuad(p2, p1, p3, p4);
        }

        if (direction.x == -1)
        {
            Vector3 p1 = loc;
            Vector3 p2 = loc + Vector3(0, blockSize.y, 0);
            Vector3 p3 = loc + Vector3(0, 0, blockSize.z);
            Vector3 p4 = loc + Vector3(0, blockSize.y, blockSize.z);
            mesh.addQuad(p2, p1, p3, p4);
        }

        if (direction.x == 1)
        {
            Vector3 p1 = loc + Vector3(blockSize.x, 0, 0);
            Vector3 p2 = loc + Vector3(blockSize.x, blockSize.y, 0);
            Vector3 p3 = loc + Vector3(blockSize.x, 0, blockSize.z);
            Vector3 p4 = loc + Vector3(blockSize.x, blockSize.y, blockSize.z);
            mesh.addQuad(p4, p3, p1, p2);
        }

        if (direction.z == -1)
        {
            Vector3 p1 = loc;
            Vector3 p2 = loc + Vector3(blockSize.x, 0, 0);
            Vector3 p3 = loc + Vector3(0, blockSize.y, 0);
            Vector3 p4 = loc + Vector3(blockSize.x, blockSize.y, 0);
            mesh.addQuad(p2, p1, p3, p4);
        }
        if (direction.z == 1)
        {
            Vector3 p1 = loc + Vector3(0, 0, blockSize.z);
            Vector3 p2 = loc + Vector3(blockSize.x, 0, blockSize.z);
            Vector3 p3 = loc + Vector3(0, blockSize.y, blockSize.z);
            Vector3 p4 = loc + Vector3(blockSize.x, blockSize.y, blockSize.z);
            mesh.addQuad(p4, p3, p1, p2);
        }
    }
};

#endif