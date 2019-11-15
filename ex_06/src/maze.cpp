#include "maze.h"

#include "mesh.h"

void Construct::maze(Mesh &mesh)
{
    // Vector3 mesh;
    Vector3 a (1.f, 0.f, 0.f);
    Vector3 b (0.f, 0.f, 0.f);
    Vector3 c (0.f, 0.f, 1.f);
    Vector3 d (1.f, 0.f, 1.f);
    mesh.addQuad(a, b, c, d);
}
 
bool Maze::isColliding(const Vector3& loc) const
{
    Vector3Int blockLoc = loc / Vector3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
    // blockLoc.x -= NB_ELEMENTS;
    // blockLoc.y -= NB_ELEMENTS;
    // blockLoc.z -= NB_ELEMENTS;

    Vector3Int chunkCoordinates = loc / Vector3(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE);
    // chunkCoordinates.x -= 1;
    // chunkCoordinates.y -= 1;
    // chunkCoordinates.z -= 1;
    for (const MazeChunk& chunk : chunks)
    {
        if (chunk.getChunkCoordinates() == chunkCoordinates)
        {
            return chunk.isBlockColliding(blockLoc);
        }
    }
    return false;
}

bool Maze::containsChunk(const Vector3Int& coord) const
{
    for (const MazeChunk& chunk : chunks)
    {
        if (chunk.getChunkCoordinates() == coord)
            return true;
    }
    return false;
}

void Maze::destroyChunks(const Vector3Int& playerLoc)
{
    for (std::vector<MazeChunk>::iterator it = chunks.begin(); it != chunks.end();)
    {
        if (abs(it->getChunkCoordinates().x - playerLoc.x) > renderDistance.x / 2 + 1
            || abs(it->getChunkCoordinates().y - playerLoc.y) > renderDistance.y / 2 + 1
            || abs(it->getChunkCoordinates().z - playerLoc.z) > renderDistance.z / 2 + 1)
            it = chunks.erase(it);
        else 
            ++it;
    }
}

void Maze::createChunks(const Vector3Int& playerLoc)
{
    for (int x = 0; x < renderDistance.x; x++)
    {
        for (int y = 0; y < renderDistance.y; y++)
        {
            for (int z = 0; z < renderDistance.z; z++)
            {
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

void Maze::render(const Vector3& playerLoc)
{
    Vector3Int playerCoordinates(playerLoc/chunkSize);//chunk

    if (lastPlayerLoc != playerCoordinates)
    {
        destroyChunks(playerCoordinates);

        createChunks(playerCoordinates);
    }

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    for (MazeChunk& chunk : chunks)
    {
        chunk.render();
    }
    glDisable(GL_CULL_FACE);
    lastPlayerLoc = playerCoordinates;
}

