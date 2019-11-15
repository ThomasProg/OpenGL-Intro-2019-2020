#ifndef _MAZE_H_
#define _MAZE_H_

#include <memory>
#include <iostream>

//#include "referential.h"
#include "macros.h"
#include "transform.h"

#include "chunk.h"

//#define COORDS3D(x, y, z, sizeY, sizeZ) (z + y * sizeZ + x * sizeY * sizeZ)

struct Mesh;

namespace Construct
{
    //meridians = horizontalRotation subUnits
    //parallels = verticalRotation subUnits
    void maze(Mesh &mesh);
};

// #include "mesh.h"

// class MazeChunk
// {
// private:
//     //S_Case* cases = nullptr;
//     std::vector<S_Block> blocks;
//     Vector3 blockSize  = Vector3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
//     Vector3Int nbElements = Vector3Int(NB_ELEMENTS, NB_ELEMENTS, NB_ELEMENTS);
// public: 
//     Mesh mesh;
//     Vector3Int coordinates = Vector3Int(0, 0, 0);
//     bool bSet = false;
//     bool bUpdate = false;
    
//     bool isBlockColliding(const Vector3Int& blockWorldLoc) const
//     {
//         Vector3Int relativeLoc = blockWorldLoc % NB_ELEMENTS;
//         //relativeLoc = Vector3Int(relativeLoc.x - 10, relativeLoc.y - 10, relativeLoc.z - 10);
//         if (relativeLoc.x < 0)
//             relativeLoc.x += NB_ELEMENTS;
//         if (relativeLoc.y < 0)
//             relativeLoc.y += NB_ELEMENTS;
//         if (relativeLoc.z < 0)
//             relativeLoc.z += NB_ELEMENTS;

//         E_BlockTypes block = blocks[getCoords3D(relativeLoc.x, relativeLoc.y, relativeLoc.z, 
//                                     NB_ELEMENTS, NB_ELEMENTS)].blockID;

//         return block == E_BlockTypes::E_SIMPLE;
//     }

//     int getCoords3D(int x, int y, int z, int sizeY, int sizeZ) const
//     {
//         return z + y * sizeZ + x * sizeY * sizeZ;
//     }

//     MazeChunk()
//     {
//         mesh.type = E_MeshType::E_MAZE;
//         mesh.typeOfVerticies = E_VerticesType::E_QUAD;
//     }

//     MazeChunk(Vector3Int& coord) : coordinates(coord)
//     {
//         mesh.type = E_MeshType::E_MAZE;
//         mesh.typeOfVerticies = E_VerticesType::E_QUAD;

//         generateChunk();

//         update();
//     }

//     ~MazeChunk()
//     {

//     }

//     void generateChunk()
//     {
//         if (coordinates.x == 0 && coordinates.y == 0 && coordinates.z == 0)
//             clearChunk();

//         else 
//         {
//             for (int x = 0; x < nbElements.x; x++)
//             {
//                 for (int y = 0; y < nbElements.y; y++)
//                 {
//                     for (int z = 0; z < nbElements.z; z++)
//                     {
//                         S_Block block = generateBlock(Vector3Int(x, y, z));
//                         blocks.emplace_back(S_Block(block));
//                     }
//                 }
//             }
//         }
//     }

//     void clearChunk()
//     {
//         blocks.clear();
//         for (int i = 0; i < nbElements.x * nbElements.y * nbElements.z; i++)
//         {
//             blocks.emplace_back(S_Block(E_BlockTypes::E_AIR));
//         }
//     }

//     E_BlockTypes generateBlock(const Vector3Int& coord)
//     {
//         int totX = coord.x + coordinates.x * nbElements.x;
//         int totZ = coord.z + coordinates.z * nbElements.z;
//         int totY = coord.y + coordinates.y * nbElements.y;
//         // if (totX == 5 && totZ == 10)
//         //     return E_BlockTypes::E_SIMPLE;

//         //if (abs(totX % 3 ) < 3 && abs(totZ % 3))
//         // if (abs(totY % 5) == 0)
//         //     return E_BlockTypes::E_AIR;
//         // if (coordinates.x == 0 && coordinates.y == 0)// && coordinates.z % 10 == 0)
//         //     return E_BlockTypes::E_AIR;

//         //return E_BlockTypes::E_SIMPLE;

//         //to generate mountains
//         bool isUnderground = false;
//         if (totY < 3*sin(totX*0.1) + 3*sin(totZ*0.1))
//         //if ((coord.y + coordinates.y * nbElements.y) % 3 == 0)
//         {
//             isUnderground = true;
//         }
//         else 
//         {
//             if (totY < 10*sin(totX*0.01+3) + 12*sin(totZ*0.01+2))
//             {
//                 isUnderground = true;
//             }
//         }

//         //uncomment to create a path to the surface
//         // if (totX == 5 && totZ == 5)
//         //     return E_BlockTypes::E_AIR;

//         if (isUnderground)
//         {
//             // if (totX % 10 == 5 && totY % 10 == 5)
//             //     return E_BlockTypes::E_AIR;
//             if (positiveModulo(totY, 10) == 5 && (positiveModulo(totZ, 10) == 5 || positiveModulo(totX, 10) == 5))
//                 return E_BlockTypes::E_AIR;
//             else 
//             {
//                 return E_BlockTypes::E_SIMPLE;
//             }
//         }
//         else 
//             return E_BlockTypes::E_AIR;
//     }

//     void update()
//     {
//         mesh.vertices.clear();
//         mesh.triangles.clear();

//         Vector3Int dir[6] = {{0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}};

//         int blockID, neighbourBlock;
//         for (int x = 0; x < nbElements.x; x++)
//         {
//             for (int y = 0; y < nbElements.y; y++)
//             {
//                 for (int z = 0; z < nbElements.z; z++)
//                 {
//                     blockID = getCoords3D(x, y, z, nbElements.y, nbElements.z);
//                     if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
//                     {
//                         for (unsigned int face = 0; face < 6; face++) //for each face
//                         {
//                             bool bDisplay = x + dir[face].x >= nbElements.x 
//                                          || y + dir[face].y >= nbElements.y
//                                          || z + dir[face].z >= nbElements.z;
//                             bDisplay = bDisplay || x + dir[face].x < 0 
//                                                 || y + dir[face].y < 0
//                                                 || z + dir[face].z < 0;
//                             if (!bDisplay)
//                             {
//                                 neighbourBlock = getCoords3D(x + dir[face].x, y + dir[face].y, z + dir[face].z, nbElements.y, nbElements.z);
//                                 //if (neighbourBlock < blocks.size())
//                                     bDisplay = blocks[neighbourBlock].blockID == E_BlockTypes::E_AIR;

//                             }
                        
//                             if (bDisplay)
//                             {
//                                 Vector3 loc ((nbElements.x + float(x)) * blockSize.x, 
//                                              (nbElements.y + float(y)) * blockSize.y, 
//                                              (nbElements.z + float(z)) * blockSize.z);
//                                 if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
//                                     blocks[blockID].addQuad(mesh, loc, blockSize, dir[face]);
//                                 //new cases[blocID] (0);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     void render()
//     {
//         glPushMatrix();

//         glTranslatef((coordinates.x - 1) * (blockSize.x * nbElements.x),
//                      (coordinates.y - 1) * (blockSize.y * nbElements.y),
//                      (coordinates.z - 1) * (blockSize.z * nbElements.z));

//         mesh.draw();

//         glPopMatrix();
//     }
// };

class Maze
{
private:
    const Vector3 chunkSize   = Vector3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);
    Vector3Int renderDistance = Vector3Int(6, 4, 6);
    Vector3Int lastPlayerLoc  = Vector3Int(50, 50, 50);

    std::vector<MazeChunk> chunks;

public:
    Maze() {}

    ~Maze() {}

    bool isColliding(const Vector3& loc) const;

    bool containsChunk(const Vector3Int& coord) const;

    void destroyChunks(const Vector3Int& playerLoc);
    void createChunks(const Vector3Int& playerLoc);

    void render(const Vector3& playerLoc);
};

#endif