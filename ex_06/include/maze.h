#ifndef _MAZE_H_
#define _MAZE_H_

#include <memory>
#include <iostream>

#include "macros.h"
#include "transform.h"

#include "chunk.h"

struct Mesh;

namespace Construct
{
    //meridians = horizontalRotation subUnits
    //parallels = verticalRotation subUnits
    void maze(Mesh &mesh);
};

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