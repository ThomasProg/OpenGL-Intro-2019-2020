#ifndef _MAZE_H_
#define _MAZE_H_

#include <memory>
#include <iostream>

#include "macros.h"
#include "transform.h"
#include "block.h"

#define COORDS3D(x, y, z, sizeY, sizeZ) z + y * sizeZ + x * sizeY * sizeZ

struct Mesh;

namespace Construct
{
    //meridians = horizontalRotation subUnits
    //parallels = verticalRotation subUnits
    void maze(Mesh &mesh);
};

#include "mesh.h"

class MazeChunk
{
private:
    //S_Case* cases = nullptr;
    std::vector<S_Block> blocks;
    Vector3 blockSize  = Vector3(1, 1, 1);
    Vector3Int nbElements = Vector3Int(10, 10, 10);
public: 
    Mesh mesh;
    Vector3Int coordinates = Vector3Int(0, 0, 0);
    bool bSet = false;
    bool bUpdate = false;
    
    MazeChunk()
    {
        //set();
    }

    MazeChunk(Vector3Int& coord) : coordinates(coord)
    {
        unsigned int blockID;
        for (int x = 0; x < nbElements.x; x++)
        {
            for (int y = 0; y < nbElements.y; y++)
            {
                for (int z = 0; z < nbElements.z; z++)
                {
                    blockID = COORDS3D(x, y, z, nbElements.y, nbElements.z);
                    S_Block block = blockGeneration(Vector3Int(x, y, z));
                    blocks.emplace_back(S_Block(block));

                    // Vector3 loc (coord.x * blockSize.x + x, coord.y * blockSize.y + y, coord.z * blockSize.z + z);
                    // if (block != E_BlockTypes::E_AIR)
                    //     blocks[blockID].addQuad(mesh, loc, blockSize);
                    //std::cout << y + coordinates.y * nbElements.y << " / "<<  -1 + sin(x) * sin(z) << std::endl;
                    //new cases[blocID] (0);
                }
            }
        }
        update();
    }

    ~MazeChunk()
    {

    }

    // void set()
    // {
    //     if (bSet)
    //         return; 

    //     bSet = true;
    //     //blocks = new S_Case[nbElements.x * nbElements.y * nbElements.z];
    //     blocks.reserve(nbElements.x * nbElements.y * nbElements.z);
    //     unsigned int blockID;
    //     for (int x = 0; x < nbElements.x; x++)
    //     {
    //         for (int y = 0; y < nbElements.y; y++)
    //         {
    //             for (int z = 0; z < nbElements.z; z++)
    //             {
    //                 blockID = COORDS3D(x, y, z, nbElements.y, nbElements.z);
    //                 blocks.emplace_back(S_Block());
    //                 //std::cout << y + coordinates.y * nbElements.y << " / "<<  -1 + sin(x) * sin(z) << std::endl;
    //                 //new cases[blocID] (0);
    //             }
    //         }
    //     }
    // }

    S_Block blockGeneration(Vector3Int coord)
    {
        int totX = coord.x + coordinates.x * nbElements.x;
        if (coord.y + coordinates.y * nbElements.y < 1*sin(totX))
        {
            return E_BlockTypes::E_SIMPLE;
            //std::cout << y << " / " << coordinates.y << " / " << nbElements.y << std::endl;
        }
        else 
        {
            //std::cout << "   / " << y << " / " << coordinates.y << " / " << nbElements.y << std::endl;
            return E_BlockTypes::E_AIR;
        }
    }

    // void update()
    // {
    //     unsigned int blockID;
    //     for (int x = 0; x < nbElements.x; x++)
    //     {
    //         for (int y = 0; y < nbElements.y; y++)
    //         {
    //             for (int z = 0; z < nbElements.z; z++)
    //             {
    //                 blockID = COORDS3D(x, y, z, nbElements.y, nbElements.z);
    //                 unsigned int blockUpID = COORDS3D(x, y+1, z, nbElements.y, nbElements.z);
    //                 blockGeneration(blockUpID, y+1);
                    
    //                 if (blockUpID > blocks.size() || blocks[blockUpID].blockID == E_BlockTypes::E_AIR)
    //                 {
    //                     blockGeneration(blockID, y);

    //                     if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
    //                     {
    //                         //std::cout << "YOP" << std::endl;
    //                         //glTranslatef(x * blockSize.x, y * blockSize.y, z * blockSize.z);
    //                         //mesh.setMesh(E_MeshType::E_CUBE);

    //                         Vector3 loc(x * blockSize.x, y * blockSize.y, z * blockSize.z);
    //                         // Vector3 p2 = p1 + Vector3(blockSize.x, 0, 0);
    //                         // Vector3 p3 = p1 + Vector3(0, blockSize.x, 0);
    //                         // Vector3 p4 = p1 + Vector3(blockSize.x, blockSize.x, 0);
    //                         // mesh.addQuad(p2, p1, p3, p4);

    //                         blocks[blockID].addQuad(mesh, loc, blockSize);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    void update()
    {
        mesh.vertices.clear();
        mesh.triangles.clear();

        Vector3Int dir[6] = {{0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1}};

        unsigned int blockID, blockUpID;
        for (int x = 0; x < nbElements.x; x++)
        {
            for (int y = 0; y < nbElements.y; y++)
            {
                for (int z = 0; z < nbElements.z; z++)
                {
                    for (unsigned int face = 0; face < 6; face++)
                    {
                        
                        blockID = COORDS3D(x, y, z, nbElements.y, nbElements.z);
                        bool bDisplay = y == nbElements.y - 1 || z == nbElements.z - 1  || x == nbElements.x - 1;
                        bDisplay = bDisplay || y == 0 || z == 0 || x == 0;
                        if (!bDisplay)
                        {
                            blockUpID = COORDS3D(x + dir[face].x, y + dir[face].y, z + dir[face].z, nbElements.y, nbElements.z);
                            if (blockUpID < blocks.size())
                                bDisplay  = blocks[blockUpID].blockID == E_BlockTypes::E_AIR;
                        }

                        if (bDisplay)
                        {
                            Vector3 loc (coordinates.x * blockSize.x + x, coordinates.y * blockSize.y + y, coordinates.z * blockSize.z + z);
                            if (blocks[blockID].blockID != E_BlockTypes::E_AIR)
                                blocks[blockID].addQuad(mesh, loc, blockSize, dir[face]);
                            //std::cout << y + coordinates.y * nbElements.y << " / "<<  -1 + sin(x) * sin(z) << std::endl;
                            //new cases[blocID] (0);
                        }
                    }
                }
            }
        }
    }

    void render()
    {
        // glCullFace(GL_BACK);
        // glEnable(GL_CULL_FACE);
        glPushMatrix();

        glTranslatef(coordinates.x * blockSize.x * nbElements.x,
                     coordinates.y * blockSize.y * nbElements.y,
                     coordinates.z * blockSize.z * nbElements.z);

        mesh.draw();

        glPopMatrix();
        //glDisable(GL_CULL_FACE);
    }
};

class Maze
{
private:
    const double chunkSize = 10.f;
    Vector3Int renderDistance = Vector3Int(5, 5, 5);

public:
    std::vector<MazeChunk> chunks;
    Maze()
    {
        // chunks.reserve(renderDistance.x * renderDistance.y * renderDistance.z);
        // for (int x = 0; x < renderDistance.x; x++)
        // {
        //     for (int y = 0; y < renderDistance.y; y++)
        //     {
        //         for (int z = 0; z < renderDistance.z; z++)
        //         {
        //             chunks.emplace_back(MazeChunk());
        //         }
        //     }
        // }
    }

    bool containsChunk(Vector3Int coord)
    {
        for (MazeChunk& chunk : chunks)
        {
            if (chunk.coordinates == coord)
                return true;
        }
        return false;
    }

    void destroyChunks(const Vector3Int& playerLoc)
    {
        for (std::vector<MazeChunk>::iterator it = chunks.begin(); it != chunks.end(); it++)
        {
            if (abs(it->coordinates.x - playerLoc.x) > renderDistance.z/2 + 5
                || abs(it->coordinates.x - playerLoc.x) > renderDistance.z/2 + 5
                || abs(it->coordinates.x - playerLoc.x) > renderDistance.z/2 + 5)
                it = chunks.erase(it);
            else 
                ++it;
        }
    }

    void createChunks(const Vector3Int& playerLoc)
    {
        int chunkID;
        for (int x = 0; x < renderDistance.x; x++)
        {
            for (int y = 0; y < renderDistance.y; y++)
            {
                for (int z = 0; z < renderDistance.z; z++)
                {
                    //chunkID = COORDS3D(x, y, z, renderDistance.y, renderDistance.z);
                    Vector3Int chunkCoord (x - renderDistance.x / 2 + playerLoc.x, 
                                           y - renderDistance.y / 2 + playerLoc.y, 
                                           z - renderDistance.z / 2 + playerLoc.z);

                    if (!containsChunk(chunkCoord))
                    {
                        chunks.push_back(MazeChunk(chunkCoord));
                    }
                }
            }
        }
    }

    void tick()
    {

    }

    void render(const Vector3& playerLoc)
    {
        Vector3Int playerCoordinates(playerLoc/chunkSize);//chunk

        destroyChunks(playerCoordinates);

        createChunks(playerCoordinates);

        for (MazeChunk& chunk : chunks)
        {
            chunk.render();
        }
        // int chunkID;
        // for (int x = 0; x < renderDistance.x; x++)
        // {
        //     for (int y = 0; y < renderDistance.y; y++)
        //     {
        //         for (int z = 0; z < renderDistance.z; z++)
        //         {
        //             //chunkID = COORDS3D(x, y, z, renderDistance.y, renderDistance.z);
        //             chunks[chunkID].coordinates = Vector3Int(x - renderDistance.x / 2 + playerCoordinates.x, 
        //                                                      y - renderDistance.y / 2 + playerCoordinates.y, 
        //                                                      z - renderDistance.z / 2 + playerCoordinates.z);

        //             //chunks[chunkID].set();
        //             //chunks[chunkID].update();
        //             chunks[chunkID].render();
        //         }
        //     }
        // }
    }
};

#endif