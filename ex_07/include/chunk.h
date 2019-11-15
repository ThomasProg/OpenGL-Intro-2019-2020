#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "mesh.h"
#include "block.h"

int positiveModulo(int n, int modulo);

class MazeChunk
{
private:
    std::vector<S_Block> blocks;
    Vector3 blockSize  = Vector3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
    Vector3Int nbElements = Vector3Int(NB_ELEMENTS, NB_ELEMENTS, NB_ELEMENTS);
    Mesh mesh;
    Vector3Int coordinates = Vector3Int(0, 0, 0);
    
public: 

    inline
    Vector3Int getChunkCoordinates() const {return coordinates;};

    bool isBlockColliding(const Vector3Int& blockWorldLoc) const;

    int getCoords3D(int x, int y, int z, int sizeY, int sizeZ) const;

    MazeChunk();

    MazeChunk(Vector3Int& coord);

    ~MazeChunk() {}

    void generateChunk(); //generate chunk blocks and puts them into "blocks" array

    void clearChunk(); //set all blocks to air

    E_BlockTypes generateBlock(const Vector3Int& coord); //returns block ID at given location

    //Update vertices, used to render.
    //If you modify "blocks", you will get render errors without calling this function.
    void update();

    void render();
};

#endif