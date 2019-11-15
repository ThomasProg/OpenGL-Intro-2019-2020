#include "chunk.h"

int positiveModulo(int n, int modulo) //true mathematic version 
{
    n %= modulo;
    if (n < 0)
        n += modulo;
    return n;
}


bool MazeChunk::isBlockColliding(const Vector3Int& blockWorldLoc) const
{
    Vector3Int relativeLoc = blockWorldLoc % NB_ELEMENTS;
    if (relativeLoc.x < 0)
        relativeLoc.x += NB_ELEMENTS;
    if (relativeLoc.y < 0)
        relativeLoc.y += NB_ELEMENTS;
    if (relativeLoc.z < 0)
        relativeLoc.z += NB_ELEMENTS;

    E_BlockTypes block = blocks[getCoords3D(relativeLoc.x, relativeLoc.y, relativeLoc.z, 
                                NB_ELEMENTS, NB_ELEMENTS)].blockID;

    return block == E_BlockTypes::E_SIMPLE;
}

int MazeChunk::getCoords3D(int x, int y, int z, int sizeY, int sizeZ) const
{
    return z + y * sizeZ + x * sizeY * sizeZ;
}

MazeChunk::MazeChunk()
{
    mesh.type = E_MeshType::E_MAZE;
    mesh.typeOfVerticies = E_VerticesType::E_QUAD;
}

MazeChunk::MazeChunk(Vector3Int& coord) : coordinates(coord)
{
    mesh.type = E_MeshType::E_MAZE;
    mesh.typeOfVerticies = E_VerticesType::E_QUAD;

    generateChunk();

    update();
}

void MazeChunk::generateChunk()
{
    if (coordinates.x == 0 && coordinates.y == 0 && coordinates.z == 0)
        clearChunk();
    else 
    {
        for (int x = 0; x < nbElements.x; x++)
        {
            for (int y = 0; y < nbElements.y; y++)
            {
                for (int z = 0; z < nbElements.z; z++)
                {
                    S_Block block = generateBlock(Vector3Int(x, y, z));
                    blocks.emplace_back(S_Block(block));
                }
            }
        }
    }
}

void MazeChunk::clearChunk()
{
    blocks.clear();
    for (int i = 0; i < nbElements.x * nbElements.y * nbElements.z; i++)
    {
        blocks.emplace_back(S_Block(E_BlockTypes::E_AIR));
    }
}

E_BlockTypes MazeChunk::generateBlock(const Vector3Int& coord)
{
    int totX = coord.x + coordinates.x * nbElements.x;
    int totZ = coord.z + coordinates.z * nbElements.z;
    int totY = coord.y + coordinates.y * nbElements.y;
    // if (totX == 5 && totZ == 10)
    //     return E_BlockTypes::E_SIMPLE;

    //if (abs(totX % 3 ) < 3 && abs(totZ % 3))
    // if (abs(totY % 5) == 0)
    //     return E_BlockTypes::E_AIR;
    // if (coordinates.x == 0 && coordinates.y == 0)// && coordinates.z % 10 == 0)
    //     return E_BlockTypes::E_AIR;

    //return E_BlockTypes::E_SIMPLE;

    //to generate mountains
    bool isUnderground = false;
    if (totY < 3*sin(totX*0.1) + 3*sin(totZ*0.1))
    //if ((coord.y + coordinates.y * nbElements.y) % 3 == 0)
    {
        isUnderground = true;
    }
    else 
    {
        if (totY < 10*sin(totX*0.01+3) + 12*sin(totZ*0.01+2))
        {
            isUnderground = true;
        }
    }

    //uncomment to create a path to the surface
    // if (totX == 5 && totZ == 5)
    //     return E_BlockTypes::E_AIR;

    if (isUnderground)
    {
        // if (totX % 10 == 5 && totY % 10 == 5)
        //     return E_BlockTypes::E_AIR;
        if (positiveModulo(totY, 10) == 5 && (positiveModulo(totZ, 10) == 5 || positiveModulo(totX, 10) == 5))
            return E_BlockTypes::E_AIR;
        else 
        {
            return E_BlockTypes::E_SIMPLE;
        }
    }
    else 
        return E_BlockTypes::E_AIR;
}

void MazeChunk::update()
{
    mesh.vertices.clear();
    mesh.triangles.clear();
    mesh.normals.clear();

    Vector3Int dir[6] = {{0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}};

    int blockID, neighbourBlock;
    for (int x = 0; x < nbElements.x; x++)
    {
        for (int y = 0; y < nbElements.y; y++)
        {
            for (int z = 0; z < nbElements.z; z++)
            {
                blockID = getCoords3D(x, y, z, nbElements.y, nbElements.z);
                if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
                {
                    for (unsigned int face = 0; face < 6; face++) //for each face
                    {
                        bool bDisplay = x + dir[face].x >= nbElements.x 
                                        || y + dir[face].y >= nbElements.y
                                        || z + dir[face].z >= nbElements.z;
                        bDisplay = bDisplay || x + dir[face].x < 0 
                                            || y + dir[face].y < 0
                                            || z + dir[face].z < 0;

                        //If the face is displaying it means it is at the border of the chunk.
                        //Them, if it is not, it means it is between other blocks (at the border) of the chunk.
                        //That means the neighbourBlock is always inside the same chunk.
                        //That is why we do not test it. 
                        if (!bDisplay)
                        {
                            neighbourBlock = getCoords3D(x + dir[face].x, y + dir[face].y, z + dir[face].z, nbElements.y, nbElements.z);
                            bDisplay = blocks[neighbourBlock].blockID == E_BlockTypes::E_AIR;

                        }
                    
                        if (bDisplay)
                        {
                            Vector3 loc ((nbElements.x + float(x)) * blockSize.x, 
                                            (nbElements.y + float(y)) * blockSize.y, 
                                            (nbElements.z + float(z)) * blockSize.z);
                            if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
                                blocks[blockID].addQuad(mesh, loc, blockSize, dir[face]);
                        }
                    }
                }
            }
        }
    }
}

void MazeChunk::render()
{
    glPushMatrix();

    glTranslatef((coordinates.x - 1) * (blockSize.x * nbElements.x),
                    (coordinates.y - 1) * (blockSize.y * nbElements.y),
                    (coordinates.z - 1) * (blockSize.z * nbElements.z));

    mesh.draw();

    glPopMatrix();
}