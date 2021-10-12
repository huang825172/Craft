#include "world.h"

#include <math.h>

World::World()
{
    rootChunk = std::make_shared<Chunk>();
}

void World::Tick()
{
}

std::shared_ptr<Block> World::getBlock(int x, int y)
{
    bool coordNegative[2];
    coordNegative[0] = x < 0;
    coordNegative[1] = y < 0;

    Vec2i chunkCoord = {abs(x) / chunkSize, abs(y) / chunkSize};
    if (coordNegative[0])
        chunkCoord.x = -1 - chunkCoord.x;
    if (coordNegative[1])
        chunkCoord.y = -1 - chunkCoord.y;

    std::shared_ptr<Chunk> currentChunk = rootChunk;
    Vec2i currentCoord = currentChunk->coord;

    if (cachedChunk && cachedChunk->coord % chunkCoord < currentCoord % chunkCoord)
    {
        currentChunk = cachedChunk;
        currentCoord = currentChunk->coord;
    }

    while (currentCoord != chunkCoord)
    {
        Direction step;
        if (chunkCoord.x > currentCoord.x)
            step = Direction::Right;
        else if (chunkCoord.x < currentCoord.x)
            step = Direction::Left;
        else if (chunkCoord.y > currentCoord.y)
            step = Direction::Up;
        else if (chunkCoord.y < currentCoord.y)
            step = Direction::Down;
        if (!currentChunk->links[step])
        {
            currentChunk->links[step] = Chunk::initialize(
                currentCoord + Vec2i::FromDirection(step));
        }
        currentChunk = currentChunk->links[step];
        currentCoord = currentChunk->coord;
    }

    cachedChunk = currentChunk;

    Vec2i blockCoord = Vec2i{x, y} - chunkCoord * chunkSize;
    return currentChunk->blocks[blockCoord.x][blockCoord.y];
}